------
create table constants
(
    id bigint generated always as identity
        constraint constants_pk primary key,
    name varchar(30),
    value float4
);
alter table constants
    owner to charapennikaurm;

insert into constants(name, value) VALUES ('MЗП', 482.30);

create function check_price(price float4) returns boolean
    returns null on null input
    return price <= 5 * (select value from constants where id = 1);
------
create table clients
(
    id          bigint generated always as identity
        constraint clients_pk
            primary key,
    client_name varchar(60)
);
alter table clients
    owner to charapennikaurm;


create table manufacturers
(
    id                bigint generated always as identity
        constraint manufacturers_pk
            primary key,
    manufacturer_name varchar(30)
);
alter table manufacturers
    owner to charapennikaurm;


create table order_types
(
    id             bigint not null
        constraint order_types_pk
            primary key,
    ordertype_name varchar(30)
);
alter table order_types
    owner to charapennikaurm;

create table products
(
    id              bigint generated always as identity
        constraint products_pk
            primary key,
    product_name    varchar(30),
    id_manufacturer bigint not null
        constraint products_manufacturers_null_fk
            references manufacturers (id)
            on update cascade on delete restrict
);
alter table products
    owner to charapennikaurm;


create table workers
(
    id            bigint generated always as identity
        constraint workers_pk
            primary key,
    qualification varchar(30) not null,
    worker_name   varchar(30)
);
alter table workers
    owner to charapennikaurm;

create table work_types
(
    id            bigint generated always as identity
        constraint work_types_pk
            primary key,
    worktype_name varchar(30),
    id_worker     bigint default null
        constraint work_types_workers_null_fk
            references workers (id)
);
alter table work_types
    owner to charapennikaurm;

insert into work_types(worktype_name) values ('диагностика');

create table orders
(
    id           bigint generated always as identity
        constraint orders_pk
            primary key,
    price        float4                 not null,
    location     varchar(30),
    is_guarantee boolean default true not null,
    id_product   bigint               not null
        unique
        constraint orders_products_null_fk
            references products (id)
            on update cascade on delete cascade,
    id_client    bigint               not null
        constraint orders_clients_null_fk
            references clients (id)
            on update cascade on delete restrict,
    stage     varchar(30) not null,
    id_ordertype bigint default 1  not null
        constraint orders_order_types_null_fk
            references order_types (id)
            on update cascade on delete restrict,
    id_worktype bigint                not null
        constraint orders_work_types_null_fk
            references work_types (id)
            on update cascade on delete restrict,

    constraint orders_price_check check ( check_price(price)),
    constraint orders_stage_check check (
        stage in  ('принята', 'проверка', 'выполнено', 'отложено', 'отказано')
    )
);
alter table orders
    owner to charapennikaurm;

create table equipments
(
    id             bigint generated always as identity
        constraint equipments_pk
            primary key,
    equipment_name varchar(30)
);
alter table equipments
    owner to charapennikaurm;

create table equipments_orders(
    id_equipment bigint
        constraint equipments_orders_equipments_null_fk
            references equipments (id),
    id_order bigint
        constraint equipments_orders_orders_null_fk
            references orders (id),
    constraint equipments_orders_pk primary key (id_order, id_equipment)
);
alter table equipments_orders
    owner to charapennikaurm;






