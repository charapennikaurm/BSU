--1
create or replace function calclulate_premium(doctor_id bigint) returns numeric(8, 2)
return 0.1 * (
select sum(s.price)
from visit v
inner join services s on s.code_srv = v.code_srv
where v.id_doctor = doctor_id
)

--2
create or replace function calculate_total_price(
patient_n_card numeric(6),
start_date date,
end_date date default null
) returns numeric(8, 2)
return (
select sum(s.price)
from visit v
inner join services s on s.code_srv = v.code_srv
where (
    id_patient = patient_n_card
    and visit_date >= start_date
    and (end_date is null or visit_date <=  end_date)
    )
);

--3
create or replace function calculate_sale(patient_n_card numeric(4)) returns numeric(2)
return (select case
                   when calculate_total_price < 50 then 3
                   when calculate_total_price >= 50 and calculate_total_price < 100 then 10
                   when calculate_total_price >= 100 and calculate_total_price < 200 then 20
                   when calculate_total_price >= 200 and calculate_total_price < 400 then 30
                   when calculate_total_price >= 400 then 40
                   end sale
        from (select * from calculate_total_price(patient_n_card, (select min(visit_date) from visit))) tp);

--4
create or replace function num_visits(doctor_id numeric(4)) returns int
return (select count(*)
from visit v
inner join doctor d on v.id_doctor = d.id_doctor
where d.id_doctor = doctor_id);

--5
create or replace function max_visit_difference(
    start_date date,
    end_date date default null
) returns int
    return (
        select max(nv.num_visits) - min(nv.num_visits)
        from(
        select id_doctor, count(*) as num_visits
        from visit v
        where (
            v.id_doctor is not null
            and v.visit_date >= start_date
            and (end_date is null or v.visit_date <= end_date)
        )
        group by id_doctor
        ) as nv
    );

--6

create or replace function calculate_bonus_by_id(
doctor_id numeric(4),
start_date date default null,
end_date date default null
) returns numeric(9,2)
    return (select coalesce(b, 0) from
        (
        select
        case
            when tp < 50 then 0.1 * tp
            when tp >= 50 and tp < 100 then 0.15 * tp
            when tp >= 100 and tp < 400 then 0.3 * tp
            when tp >= 400 then 0.5 * tp
        end as b
        from
        (
        select sum(s.price) as tp
        from doctor d2
        left outer join visit v on d2.id_doctor = v.id_doctor
        inner join services s on v.code_srv = s.code_srv
        where (
                d2.id_doctor = doctor_id
                and
                (start_date is null or v.visit_date >= start_date)
                and
                (end_date is null or v.visit_date <= end_date)
              )
        )
        as total_price
        ) as bonus);

create or replace procedure assign_bonus_by_id(
doctor_id numeric(4),
start_date date default null,
end_date date default null
)
language sql
as $$
update doctor
set bonus = calculate_bonus_by_id(doctor_id, start_date, end_date)
where doctor.id_doctor = doctor_id
$$

create or replace procedure assign_bonus_by_surname(
surname_ varchar(50),
start_date date default null,
end_date date default null
)
language sql
as $$
update doctor
set bonus = calculate_bonus_by_id(id_doctor, start_date, end_date)
where doctor.surname = surname_
$$



create or replace procedure assign_bonus_by_speciality(
spec varchar(50),
start_date date default null,
end_date date default null
)
language sql
as $$
    update doctor d
    set
        bonus = calculate_bonus_by_id(d.id_doctor, start_date, end_date)
    from speciality s
    where s.title = spec and d.code_spec = s.code_spec
$$

create or replace procedure assign_bonus(
id_doctor numeric(4) default null,
doctor_surname varchar(50) default null,
spec varchar(20) default null,
start_date date default null,
end_date date default null
)
language plpgsql
as $procedure$
    begin
        if (id_doctor is not null) then
            call assign_bonus_by_id(id_doctor, start_date, end_date);
        elsif (doctor_surname is not null) then
            call assign_bonus_by_surname(doctor_surname, start_date, end_date);
        elsif (spec is not null) then
            call assign_bonus_by_speciality(spec, start_date, end_date);
        else
            update doctor
            set bonus = calculate_bonus_by_id(id_doctor, start_date, end_date);
        end if;
    end;
$procedure$

--7


create or replace function get_vaccant_or_small_speciality() returns numeric(4)
    return (select sp.code_spec
            from speciality sp
            left outer join doctor d on sp.code_spec = d.code_spec
            group by sp.code_spec
            order by count(d.id_doctor)
            limit 1);


create or replace procedure move_intern()
language plpgsql
as $procedure$
    begin
        if (exists(select 1 from doctor  where code_spec = 1408))then
            with intern as (select * from doctor where doctor.code_spec = 1408 limit 1)
            update doctor
            set code_spec = get_vaccant_or_small_speciality()
            from intern
            where doctor.id_doctor = intern.id_doctor;
        end if;
    end;
$procedure$


create or replace procedure add_doctor(
surname_ varchar(50),
first_name_ varchar(50),
middle_name_ varchar(50),
spec varchar(20) default null
)
language plpgsql
as $procedure$
    begin
        if (spec is null) then
            call move_intern();
            insert into doctor (id_doctor, surname, first_name, middle_name, code_spec, bonus)
            values (nextval('seq_doc'), surname_, first_name_, middle_name_, 1408, 0);
        elsif (exists(select 1 from speciality s where s.title = spec)) then
            insert into doctor (id_doctor, surname, first_name, middle_name, code_spec, bonus)
            values (nextval('seq_doc'), surname_, first_name_, middle_name_,
            (select code_spec from speciality sp where sp.title = spec limit 1), 0);
        else
            insert into speciality (code_spec, title) values (nextval('seq_spec'), spec);
            insert into doctor (id_doctor, surname, first_name, middle_name, code_spec, bonus)
            values (nextval('seq_doc'), surname_, first_name_, middle_name_,
            (select code_spec from speciality sp where sp.title = spec limit 1), 0);

        end if;
    end;
$procedure$



--8
create or replace procedure add_patient(
surname_ varchar(50),
first_name_ varchar(50),
middle_name_ varchar(50),
addr varchar(50) default null
)
language plpgsql
as $procedure$
    begin
        if (addr in ('г. Артемовск', 'г. Черноморск', 'г. Верхнехолмск', 'г. Южногорск')) then
            insert
            into patient(n_card, surname, first_name, middle_name, address)
            values (nextval('seq_patient_1'), surname_, first_name_, middle_name_, addr);
        elsif (addr in ('г. Бердянск', 'г. Прокопьевск', 'г. Криворуков', 'г. Урюпинск')) then
            insert
            into patient(n_card, surname, first_name, middle_name, address)
            values (nextval('seq_patient_2'), surname_, first_name_, middle_name_, addr);
        else
            insert
            into patient(n_card, surname, first_name, middle_name, address)
            values (nextval('seq_patient_3'), surname_, first_name_, middle_name_, addr);
        end if;
    end;
$procedure$

--9
create or replace procedure move_visit(start_date date, end_date date)
language sql
as $$
update visit v
set visit_date = end_date
where visit_date = start_date
$$

--10
create or replace procedure delete_visits(start_date date, end_date date)
language plpgsql
as $procedure$
    begin
        insert
        into archive_visits(visit_date, doctor_full_name, n_patients, total_price)
        select
            v.visit_date as visit_date,
            concat(d.first_name, ' ', d.middle_name, ' ', d.surname) as full_name,
            count(*) as num_patients,
            sum(s.price) as total_price
            from visit v
            inner join doctor d on d.id_doctor = v.id_doctor
            inner join services s on v.code_srv = s.code_srv
            where v.visit_date >= start_date and v.visit_date <= end_date
            group by full_name, visit_date;
        delete
        from visit v2
        where v2.visit_date >= start_date and v2.visit_date <= end_date;
    end;
$procedure$