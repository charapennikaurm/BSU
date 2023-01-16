--1
insert into products(product_name, id_manufacturer) values ('MacBookPro16', 1);
insert into orders (price, location, id_product, id_client, stage, id_worktype)
values (200.0, 'Minsk',7 , 3,'проверка', 5);
--2
create or replace function get_top_worker(pid bigint) returns bigint
    return (select tw.topw from
                               (
    with man_tw as (select p.id_manufacturer as man,
    mode() within group (order by id_worktype) as topw
    from orders o
    inner join products p on p.id = o.id_product
    group by p.id_manufacturer)
    select man_tw.topw, p.id as prid, man_tw.man as manudacturer
    from man_tw inner join products p on p.id_manufacturer = man_tw.man
    )
    as tw
    where tw.prid = pid
    );

update orders
set id_worktype = get_top_worker(id_product);
--3
create table order_archive(
    id bigint not null generated always as  identity
        constraint order_archive_pk primary key,
    order_id bigint,
    product_name varchar(30),
    manufacturer_name varchar(30)
);
insert into order_archive (order_id, product_name, manufacturer_name)
select o.id, p.product_name, m.manufacturer_name
from orders o
inner join products p on o.id_product = p.id
inner join manufacturers m on m.id = p.id_manufacturer
where stage = 'отказано';
delete from orders
where stage='отказано';

