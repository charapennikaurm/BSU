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

