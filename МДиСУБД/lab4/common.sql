-- 1
update services set price=1 where price < 1;
-- 2
update services set price = (1.1 * services.price)
                where
                    services.price >= 10
                    and services.price <= 50
                    and services.title <> 'Ренгеноскопия';
-- 3
update services set price=
    case
        when code_srv in (
        select distinct v.code_srv
        from visit v
        inner join doctor d on d.id_doctor = v.id_doctor
        inner join speciality s on d.code_spec = s.code_spec
        where s.title = 'Терапевт'
        ) then (1.1 * services.price)
        when code_srv in (
        select distinct v.code_srv
        from visit v
        inner join doctor d on d.id_doctor = v.id_doctor
        inner join speciality s on d.code_spec = s.code_spec
        where s.title = 'Невролог'
        ) then (1.2 * services.price)
        else services.price
    end;
-- 4
update services set
price = 0.9 * (
select avg(srv.price) from visit v
inner join doctor d on d.id_doctor = v.id_doctor
inner join speciality s on s.code_spec = d.code_spec
inner join services srv on srv.code_srv = v.code_srv
where s.title = 'Терапевт' group by srv.price
)
where code_srv in (
select v.code_srv
from visit v
inner join doctor d on d.id_doctor = v.id_doctor
inner join speciality s on s.code_spec = d.code_spec
where s.title = 'Хирург'
) and price in (select min(srv.price) from services srv);
-- 5
update doctor set first_name=lower(first_name) where first_name like 'С%';
-- 6
update doctor set surname=replace(
    initcap(replace(surname, '-', ' ')),
    ' ',
    '-'
    ) where surname like '%-%';
-- 7
update doctor set surname=upper(surname);
-- 8
update visit v1 set id_doctor = (
    select v.id_doctor
    from visit v
    inner join doctor d on d.id_doctor = v.id_doctor
    where v.id_doctor <> v1.id_doctor and d.code_spec in (
        select d1.code_spec
        from doctor d1
        where d1.id_doctor = v1.id_doctor
        )
    limit 1
    )
where code_srv in (select code_srv from services where title='Консультация');
-- 9
insert into doctor
(id_doctor, surname, first_name, middle_name, code_spec)
values (nextval('seq_doc'), 'Cherepennikov', 'Roman', 'Mikhailovich', 1408);
-- 10
insert into visit
(n_visit, id_doctor, id_patient, visit_date, code_srv)
values (nextval('seq_visit'), 31, 116001, '20222-11-27', 110);
-- 11
create table tmp_doc (
    id_tmp_doctor numeric(4) not null
        constraint tmp_doc_pk
            primary key,
    surname varchar(50),
    first_name varchar(50),
    middle_name varchar(50),
    code_spec numeric(10) not null
);

alter table tmp_doc add constraint spec_doctor foreign key (code_spec) references speciality (code_spec);

insert into tmp_doc(id_tmp_doctor, surname, first_name, middle_name, code_spec)
select distinct d.id_doctor, d.surname, d.first_name, d.middle_name, d.code_spec
from doctor d inner join visit v on d.id_doctor = v.id_doctor;
-- 12
delete from tmp_doc;
-- 13
insert into tmp_doc (id_tmp_doctor, surname, first_name, middle_name, code_spec)
select distinct d.id_doctor, d.surname, d.first_name, d.middle_name, d.code_spec
from doctor d
left outer join visit v on d.id_doctor = v.id_doctor
where v.visit_date is null
    or v.visit_date < '2022-09-12'::date
    or v.visit_date > '2022-09-17'::date;
-- 14
insert into tmp_doc (id_tmp_doctor, surname, first_name, middle_name, code_spec)
select distinct d.id_doctor, d.surname, d.first_name, d.middle_name, d.code_spec
from doctor d
left outer join visit v on d.id_doctor = v.id_doctor
where v.visit_date is null
on conflict (id_tmp_doctor) do nothing;
-- 15
create table tmp_spec (
	code_spec numeric(4) not null
	    constraint tmp_spec_pk
	    primary key,
	title varchar(50) null
);
insert into tmp_spec (code_spec, title)
select code_spec, title from speciality
where (title not in (
     select distinct sp.title
        from speciality sp
        inner join doctor doc on sp.code_spec = doc.code_spec
    ));
-- 16
delete from visit where (
    visit_date <=(
    select min(visit_date)
    from visit
    limit 1) + interval '7 DAYS'
);
-- 17
delete from visit where id_doctor not in (
    select id_doctor from visit where visit_date = (select now() - interval '1 DAY')
    );

-- 18
delete from services where code_srv not in (select distinct s.code_srv
                                                   from services s inner join visit v
                                                                              on v.code_srv = s.code_srv
                                               where v.visit_date = (select now() - interval '1 DAY'));
-- 19
delete from doctor where id_doctor not in (select distinct d.id_doctor
                                              from doctor d inner join visit v
                                                                      on v.id_doctor = d.id_doctor);
-- 20
delete from tmp_spec;
delete from tmp_doc;