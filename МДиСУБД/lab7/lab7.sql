--1

create or replace procedure add_order(
client_name_ varchar(60),
product_name_ varchar(30),
product_buy_date_ date,
manufacturer_name_ varchar(30)
)
language plpgsql
as $procedure$
    begin
        if (not exists(select 1 from manufacturers where manufacturer_name = manufacturer_name_)) then
            insert into manufacturers (manufacturer_name)
            values (manufacturer_name_);
        end if;

        if (not exists(select 1 from clients where client_name = client_name_)) then
                insert into clients (client_name)
                values (client_name_);
            end if;

        insert into products(product_name, id_manufacturer, buy_date)
        values (product_name_, (select manufacturers.id from manufacturers where manufacturer_name = manufacturer_name_), product_buy_date_);

        insert into orders(price, location, is_guarantee, id_product, id_client, stage, id_ordertype, id_worktype, order_date)
        values(
               0.0, 'Minsk', (product_buy_date_ + interval '2' month >= (select current_date)),  (select last_value from products_id_seq),
               (select id from clients where client_name = client_name_),
               'принята', 3, 2, (select current_date)
              );
    end;
$procedure$


call add_order(
    'Иван Ивонович',
    'Apple Iphone 13 Pro Max Blue',
    '2022-08-12'::date,
    'Apple'
);

--2

create or replace function get_bill(
order_id bigint default null,
client_name_ varchar(60) default null,
order_date_ date default null
) returns float4
return (
        select sum(o.price) + sum(e.price) as total_price
        from orders o
        inner join clients c on o.id_client = c.id
        inner join equipments_orders eo on o.id = eo.id_order
        inner join equipments e on eo.id_equipment = e.id
        where (
                  o.is_guarantee = false
                  and
                  (order_id is not null or order_date_ is not null)
                  and
                  (order_id is null or o.id = order_id)
                  and
                  (client_name_ is null or client_name_ = c.client_name)
                  and
                  (order_date_ is null or o.order_date = order_date)
              )
);

select * from get_bill(3);
select * from get_bill(order_date_ := '2022-12-06'::date, client_name_ := 'Иванов Иван');

--3

create or replace function get_qualifications_by_manufacturer(
id_manuf bigint
) returns varchar [] as
$$
begin
    if (id_manuf in (1, 2)) then
        return array['1 разряд'];
    elsif (id_manuf) in (3) then
        return array ['1 разряд', '2 разряд'];
    else
        return array ['1 разряд', '2 разряд', '3 разряд'];
    end if;
end;
$$
language plpgsql;


create or replace function check_qualification()
returns trigger as $$
begin
    if not exists (
        select 1 from orders o
        inner join work_types wt on wt.id = o.id_worktype
        inner join workers w on wt.id_worker = w.id
        inner join products p on p.id = o.id_product
        where (
                  (w.id = NEW.id_worker)
                  and (
                      w.qualification in
                           (
                            select unnest(get_qualifications_by_manufacturer) from get_qualifications_by_manufacturer(4)
                           )
                  )
              )
        ) then
        raise exception 'The specialist''s qualification does not match the work type';
    end if;
    return new;
end;
$$ language plpgsql;

create trigger check_qualification_trigger
before insert or update on orders
for each row
execute procedure check_qualification();

update orders o
set id_worktype = 8
where o.id = 3;

update orders o
set id_worktype = 4
where o.id = 3;

