-- рефлексивное
select  w.worker_name as worker_name, f.worker_name as foreman_name
    from workers w
    inner join workers f on w.foreman_id = f.id;
-- простой CASE
select worker_name,
       case qualification
        when '1 разряд' then 'Senior'
        when '2 разряд' then 'Middle'
        when '3 разряд' then 'Junior'
        else 'Unknown'
        end as grade
from workers;
-- поисковый CASE
select o2.id,
       o2.price,
       case
           when (o2.price < (select min(o.price) + 50 from orders o)) then 'Cheap'
           when (
               o2.price >= (select min(o.price) + 50 from orders o)
               and o2.price <= (select max(o.price) - 50 from orders o)
           ) then 'Normal'
           else 'Expensive'
       end as price_group
from orders o2;
-- оператор WITH
with first_client_oreders as (
    select * from orders where id_client = 1
)
select p.product_name
from first_client_oreders o
inner join products p on p.id = o.id_product;
-- встроенное представление
create view specialists as (
select w.worker_name, array_agg(wt.worktype_name)
from workers w
inner join work_types wt on w.id = wt.id_worker
group by w.worker_name
);
select * from specialists;
-- некоррелированный
select * from orders
where price = (select min(o2.price) from orders o2);
-- коррелированный
select worktype_name from work_types wt
where exists(select * from orders o where o.id_worktype = wt.id);
-- NULLIF
select nullif(stage, 'проверка') from orders;
-- top-n анализ
select price from orders order by price desc limit 2;
-- rollup
select m.manufacturer_name as manufacture, p.product_name as product, sum(o.price) as total_price
from orders o
inner join products p on p.id = o.id_product
inner join manufacturers m on m.id = p.id_manufacturer
group by rollup (manufacture, product);
