create table visit
(
    n_visit    bigint    not null
        constraint visit_pk
            primary key,
    id_doctor  bigint    not null
        constraint visit_doctor_null_fk
            references doctor
            on delete cascade,
    id_patient integer   not null
        constraint visit_patient_null_fk
            references patient
            on delete cascade,
    date_visit timestamp not null
        constraint visit_date_check
            check ((date_visit > '2022-01-01 00:00:00'::timestamp without time zone) AND
                   (date_visit < '2022-12-31 10:23:54'::timestamp without time zone)),
    id_service bigint    not null
        constraint visit_services_null_fk
            references services
            on delete cascade
);

alter table visit
    owner to charapennikaurm;

