--1
select * from calclulate_premium(11::bigint);
select * from calclulate_premium(13::bigint);
--2
select * from calculate_total_price(116002, '2022-09-12'::date);
select * from calculate_total_price(116003, '2022-09-12'::date, '2022-09-25'::date);
--3
select * from calculate_sale(116002);
select * from calculate_sale(116003);
--4
select * from num_visits(11);
select * from num_visits(21);
--5
select * from max_visit_difference('2022-09-12'::date);
select * from max_visit_difference('2022-09-12'::date, '2022-09-16'::date);
--6
call assign_bonus(doctor_surname := 'Кисегач');
call assign_bonus(id_doctor := 11, start_date := '2022-09-12', end_date := '2022-09-12');
call assign_bonus(spec := 'Терапевт');
--7
call add_doctor('F', 'F', 'F');
call add_doctor('F', 'F', 'Ч', 'Терапевт');
call add_doctor('F', 'F', 'Ч', 'Новая специальность');
--8
call add_patient('A', 'B', 'C', 'г. Черноморск');
call add_patient('П', 'П', 'П');
call add_patient('D', 'e', 'F', 'г. Прокопьевск');
--9
call move_visit('2022-09-27'::date, '2022-09-29'::date);
call move_visit('2022-09-28'::date, '2022-09-29'::date);
--10
call delete_visits('2022-09-13'::date, '2022-09-13'::date);