create table speciality
(
    code_spes bigint not null
        constraint speciality_pk
            primary key,
    title     varchar(30)
);

alter table speciality
    owner to charapennikaurm;

