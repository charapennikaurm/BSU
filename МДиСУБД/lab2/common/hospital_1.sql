create table speciality
(
    code_spes bigint not null
        constraint speciality_pk
            primary key,
    title     varchar(30)
);

alter table speciality
    owner to charapennikaurm;

create table doctor
(
    id_doctor     bigint not null
        constraint doctor_pk
            primary key,
    surname       varchar(30),
    doctor_name   varchar(30),
    middle_name   integer,
    id_speciality bigint not null
        constraint doctor_speciality_fk
            references public.speciality(code_spes)
            on delete cascade
);

alter table doctor
    owner to charapennikaurm;

create table patient
(
    n_card       bigint  not null
        constraint patient_pk
            primary key,
    address      varchar(30),
    surname      varchar(30),
    patient_name varchar(30),
    middle_name  varchar(30),
    phone        varchar(20)
        constraint patient_check_phone
            check ((phone)::text ~
                   similar_to_escape('[+][0-9][0-9][0-9][(][0-9][0-9][)][0-9][0-9][0-9][-][0-9][0-9][-][0-9][0-9]'::text)),
    sector       integer not null
        constraint patient_check_sector
            check ((sector >= 1) AND (sector < 10)),
    patient_n    bigint  not null
        constraint patient_patient_n_unique
            unique
        constraint patient_patient_n_check
            check (patient_n < 1000),
    constraint patient_id_check
        check (n_card = ((sector * 1000) + patient_n))
);

alter table patient
    owner to charapennikaurm;

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

create table visit
(
    n_visit    bigint    not null
        constraint visit_pk
            primary key,
    id_doctor  bigint    not null
        constraint visit_doctor_fk
            references public.doctor(id_doctor)
            on delete cascade,
    id_patient integer   not null
        constraint visit_patient_fk
            references public.patient(n_card)
            on delete cascade,
    date_visit timestamp not null
        constraint visit_date_check
            check ((date_visit > '2022-01-01 00:00:00'::timestamp without time zone) AND
                   (date_visit < '2022-12-31 10:23:54'::timestamp without time zone)),
    id_service bigint    not null
        constraint visit_services_fk
            references public.services(code_srv)
            on delete cascade
);

alter table visit
    owner to charapennikaurm;
