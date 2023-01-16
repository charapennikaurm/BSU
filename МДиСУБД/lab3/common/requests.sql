-- =======================================
--                  3_1
-- =======================================
--1
select address
from patient
where
(
  patient.first_name = 'Самюэль' and
  patient.surname = 'Паниковский' and
  patient.middle_name = 'Михайлович'
);
--2
select *
from patient
where(
    patient.address in ('г. Урюпинск', 'г. Черноморск')
);
--3
select *
from services
where(
    price = (select min(price) from services)
);
--4
select *
from visit
where(
    visit_date < '2022-09-21'
);
--5
select count(id_doctor)
from doctor;
--6
select lower(first_name)
from doctor
where first_name like 'А%';
--7
select n_visit, id_doctor, id_patient, to_char(visit_date, 'DD/MM/YYYY') as visit_date, code_srv
from visit;
--8
select replace(
    replace(title, 'Хирург', 'Костоправ'), 'Травмвматолог', 'Костоправ'
)
from speciality;
--9
select avg(price)
from services serv
where serv.code_srv in
(
    select code_srv
    from visit vis
    group by vis.visit_date, vis.code_srv
    having count(*) >= 3
);
--10
select spec.title as speciality, array_agg(concat(doc.first_name, ' ', doc.middle_name, ' ', doc.surname)) as names
from
    speciality spec
    inner join doctor doc
        on spec.code_spec = doc.code_spec
group by speciality;
--11
select array_agg(concat(pat.surname,' ', pat.first_name, ' ', pat.middle_name)) as patients, serv.title, serv.price
       from visit vis
            inner join patient pat on vis.id_patient = pat.n_card
            inner join services serv on vis.code_srv = serv.code_srv
  where serv.price between (select min(price) from services) and (select min(price) + 50 from services)
    group by serv.title, serv.price;
--12
select vis.id_doctor, vis.id_patient, vis.visit_date, serv.title
from visit vis
inner join services serv on serv.code_srv = vis.code_srv
where vis.n_visit in (
    select vis.n_visit
    from visit vis
        inner join services serv
        on serv.code_srv = vis.code_srv
    where serv.price = (select max(price) from services)
);
--13
select spec.title as speciality, array_agg(concat(doc.first_name, ' ', doc.middle_name, ' ', doc.surname)) as names
from
    speciality spec
    natural join doctor doc
group by speciality;
--14
select vis.n_visit, vis.id_doctor, vis.visit_date, vis.code_srv,
       concat(pat.first_name, ' ', pat.middle_name, ' ', pat.surname) as patient
from visit vis
inner join patient pat on pat.n_card = vis.id_patient;
--15
select vis.n_visit, vis.visit_date, vis.code_srv,
       concat(doc.first_name, ' ', doc.middle_name, ' ', doc.surname) as doctor,
       concat(pat.first_name, ' ', pat.middle_name, ' ', pat.surname) as patient
from visit vis
inner join patient pat on pat.n_card = vis.id_patient
inner join doctor doc on vis.id_doctor = doc.id_doctor;
-- 16
-- специалисты осуществлявшие приемы с 15 по 22 сентября
select distinct concat(doc.first_name, ' ', doc.middle_name, ' ', doc.surname) as doctor
from doctor doc
inner join visit vis on vis.id_doctor = doc.id_doctor
where (vis.visit_date >= '2022-09-15' and vis.visit_date <= '2022-09-22');
--вакантные специальности
select title from speciality
where (title not in (
     select distinct sp.title
        from speciality sp
        inner join doctor doc on sp.code_spec = doc.code_spec
    ));

-- =======================================
--                  3_2
-- =======================================
--1
select doc.surname, doc.first_name, doc.middle_name
from visit vis
inner join doctor doc on doc.id_doctor = vis.id_doctor
inner join services serv on serv.code_srv = vis.code_srv
where serv.price = (select min(price) from services);
--2
select doc.surname, doc.first_name, doc.middle_name
from visit vis
inner join doctor doc on doc.id_doctor = vis.id_doctor
inner join patient pat on pat.n_card = vis.id_patient
where vis.visit_date in (
    select vis2.visit_date
    from visit vis2
    inner join patient pat2 on pat2.n_card = vis2.id_patient
    where pat2.surname like 'Безенчук' and pat2.first_name like 'Федор' and pat2.middle_name like 'Николаевич'
);
--3
select distinct concat(doc.first_name, ' ', doc.middle_name, ' ', doc.surname) as name
from visit vis
inner join doctor doc on vis.id_doctor = doc.id_doctor
inner join patient pat on vis.id_patient = pat.n_card
where (
    pat.surname like 'Паниковский' or
    pat.surname like 'Щукина' or
    pat.surname like 'Корейко'
);
--4
select distinct concat(doc.first_name, ' ', doc.middle_name, ' ', doc.surname) as name
from visit vis
inner join doctor doc on vis.id_doctor = doc.id_doctor
where vis.visit_date = any('{2022-09-15, 2022-09-20, 2022-09-24}'::date[]);
--5
select distinct id_doctor
from visit
where code_srv in
      (select code_srv
          from visit
          where visit_date = any ('{2022-09-12, 2022-09-13}'::date[])
      );
--6
select vis.visit_date
from visit vis
group by vis.visit_date
having (
    (select avg(price) from services) <
    (
    select avg(serv.price) as avg_price
    from visit vis2
        inner join services serv on serv.code_srv = vis2.code_srv
    where vis.visit_date = vis2.visit_date)
    );
--7
select doc.code_spec, doc.surname, doc.id_doctor
from doctor doc
inner join visit vis on doc.id_doctor = vis.id_doctor
where vis.visit_date in (
    select vis.visit_date from visit vis where vis.visit_date between '2022-09-15' and '2022-09-20'
    );
--8
select sp.code_spec
       from visit v
            inner join doctor d on d.id_doctor = v.id_doctor
            inner join speciality sp on sp.code_spec = d.code_spec
            inner join services s on s.code_srv = v.code_srv
   where exists(select 1 from services s2 where s2.code_srv >= 110 and s2.code_srv <= 150)
 group by sp.code_spec order by sp.code_spec asc;
--9
select s.code_spec
       from visit v
            inner join doctor d on d.id_doctor = v.id_doctor
            inner join speciality s on s.code_spec = d.code_spec
  where exists(select 1 from visit v2 where v.visit_date <= '2022-09-15'::date or v.visit_date >= '2022-09-20'::date)
group by s.code_spec order by s.code_spec asc;
--10
select (
    select spec.title
        from speciality spec
            where spec.code_spec  = doc.code_spec
    ) as speciality,
    concat(first_name, ' ', middle_name, ' ', surname) as name
from doctor doc
group by speciality, name;
--11
select cast(avg(serv.price) as int8)
       from visit vis
            inner join services serv on vis.code_srv = serv.code_srv
   group by vis.visit_date;
--12
select title, price,
        case
            when(price < 5) then 1
            when(price >= 5 and price < 10) then 2
            when(price >= 10 and price < 50 ) then 3
            else 4
        end as price_group
from services
order by price;
--13
select n_card, case when n_card <= 200000 then concat('AM', cast(n_card as varchar(30)))
                    else concat('NV', cast(n_card as varchar(30)))
               end
from patient;
--14
select
    surname,
    coalesce(first_name, '     '),
    coalesce(middle_name, '     ')
from doctor;