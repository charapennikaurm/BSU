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
            references speciality
);

alter table doctor
    owner to charapennikaurm;

