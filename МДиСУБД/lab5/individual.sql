--1
create or replace view workers_info as (
select w.id as worker_id, w.worker_name, coalesce(sum(o.price), 0) as total_price, count(o.id) as number_of_orders
from workers w
inner join work_types wt on w.id = wt.id_worker
left outer join orders o on wt.id = o.id_worktype
group by w.id, w.worker_name
);
-- rollup by manufacturer
--2

create or replace view worker_equipment as (
select w.worker_name, w.id as worker_id, e.id as equipment_id, e.equipment_name
from orders o
inner join equipments_orders eo on o.id = eo.id_order
inner join equipments e on eo.id_equipment = e.id
inner join work_types wt on wt.id = o.id_worktype
inner join workers w on wt.id_worker = w.id
);
--3

create or replace view nonguarantee_prices as(
select c.id as client_id, c.client_name, sum(o.price) as total_price
from orders o
join clients c on c.id = o.id_client
where o.is_guarantee = false
group by c.id, c.client_name
);