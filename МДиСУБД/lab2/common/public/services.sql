create table services
(
    code_srv bigint not null
        constraint services_pk
            primary key
        constraint services_id_check
            check ((code_srv >= 110) AND (code_srv <= 990) AND ((code_srv % (10)::bigint) = 0)),
    title    varchar(30),
    price    real
        constraint service_price_check
            check (price <= (1000)::double precision)
);

alter table services
    owner to charapennikaurm;

