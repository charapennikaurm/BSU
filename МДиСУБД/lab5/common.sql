--1
create or replace view therapists as (
select * from doctor
where doctor.code_spec = (select code_spec from speciality where title = 'Терапевт')
);
--2
create or replace view not_worked_on_visits as (
select * from doctor d
where not exists(select id_doctor from visit where visit.id_doctor = d.id_doctor)
);
--3
create or replace view doctor_with_patients as select d.surname as sotrudnik, s.title as speciality, count(p.n_card) as kol_patients
                                           from doctor d
                                                inner join speciality s on s.code_spec = d.code_spec
                                                inner join visit v on v.id_doctor = d.id_doctor
                                                inner join patient p on p.n_card = v.id_patient
                                       where v.visit_date >= '2022-09-15'::date and v.visit_date <= '2022-09-19'::date
                                             group by p.n_card, d.surname, s.title;
--4
create or replace view doctor_with_two_srv as select d.id_doctor, array_agg(v.visit_date), sum(srv.price)
                                          from services srv
                                               inner join visit v on v.code_srv = srv.code_srv
                                               inner join doctor d on d.id_doctor = v.id_doctor
                                     where d.surname in (select sotrudnik from doctor_with_patients) and srv.price > 0
                                           group by d.id_doctor having count(*) > 2;

