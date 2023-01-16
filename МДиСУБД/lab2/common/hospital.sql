create table speciality
(
    code_spes int4 not null
        constraint speciality_pk
            primary key,
    title     varchar(30)
    constraint code_spes_check  check(code_spes >=1401 and code_spes <= 1755)
);
alter table speciality
    owner to charapennikaurm;

create table doctor
(
    id            integer generated always as identity
        constraint doctor_pk
            primary key,
    surname       varchar(30),
    first_name    varchar(30),
    middle_name   varchar(30),
    id_speciality integer not null
        constraint doctor_speciality_null_fk
            references speciality
            on delete restrict
);
alter table doctor
    owner to charapennikaurm;

create table patient
(
    n_card      int4 not null
        constraint patient_pk
            primary key,
    address     varchar(50),
    phone       varchar(20),
    surname     varchar(30),
    first_name  varchar(30),
    middle_name varchar(30),
    n_patient   int4 generated always as identity,
    sector      int4 not null,

    constraint patient_phone_check check  ((phone)::text ~ similar_to_escape('[+][0-9][0-9][0-9][(][0-9][0-9][)][0-9][0-9][0-9][-][0-9][0-9][-][0-9][0-9]'::text)),
    constraint patient_sector_check check ( (sector >= 1) and (sector < 10)),
    constraint patient_n_card_check check (
        (sector = n_card / 100000)
        and
        (n_patient = n_card % 1000)
    ),
    constraint patient_n_patient_check check (n_patient < 1000),
    constraint patient_n_patient_unique unique (n_patient)
);
alter table patient
    owner to charapennikaurm;

create table services
(
    code_srv int4 not null
        constraint services_pk
            primary key,
    title    varchar(30),
    price    float4,

    constraint services_price_check check ( (price <= (1000)::double precision) ),
    constraint services_code_srv_check check (
        (code_srv >= 110) and (code_srv <= 990) and ((code_srv % 10) = 0)
    )
);
alter table services
    owner to charapennikaurm;

create table visit
(
    n_visit    integer   not null
        constraint visit_pk
            primary key,
    id_patient integer
        constraint visit_patient_null_fk
            references patient
            on delete set null,
    id_doctor  integer
        constraint visit_doctor_null_fk
            references doctor
            on delete set null,
    visitdate  timestamp not null,
    id_service integer   not null
        constraint visit_services_null_fk
            references services
            on delete set null,
    constraint visit_visit_date_check check (
        (
            (visitdate > '2022-01-01 00:00:00'::timestamp without time zone)
             and
            (visitdate < '2023-01-01 00:00:00'::timestamp without time zone)
        )
        )
);
alter table visit
    owner to charapennikaurm;
