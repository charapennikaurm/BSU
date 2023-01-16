CREATE TABLE doctor 
    ( 
     id_doctor NUMERIC(4) NOT NULL, 
     surname VARCHAR(50), 
     first_name VARCHAR(50), 
     middle_name VARCHAR(50),
     code_spec NUMERIC(10) not null
     );



ALTER TABLE doctor ADD CONSTRAINT doctor_pk PRIMARY KEY (id_doctor);


CREATE TABLE patient 
    ( 
     n_card NUMERIC(6) , 
     surname VARCHAR(50) , 
     first_name VARCHAR(50), 
     middle_name VARCHAR(50),
     address VARCHAR(50), 
     phone CHAR(20)
    ) 
;



ALTER TABLE patient ADD CONSTRAINT patient_pk PRIMARY KEY (n_card);



CREATE TABLE services 
    ( 
     code_srv NUMERIC(4) NOT NULL, 
     title VARCHAR(50), 
     price NUMERIC(8,2) 
    ) 
;



ALTER TABLE services 
    ADD CONSTRAINT services_pk PRIMARY KEY (code_srv);



CREATE TABLE speciality 
    ( 
     code_spec NUMERIC(10) NOT NULL,
     title VARCHAR(50)
    ) 
;



ALTER TABLE speciality ADD CONSTRAINT speciality_pk PRIMARY KEY (code_spec);



CREATE TABLE visit 
    ( 
     n_visit NUMERIC(6) NOT NULL, 
     id_doctor NUMERIC(4), 
     id_patient NUMERIC(6), 
     visit_date DATE,     
     code_srv NUMERIC(4)     
    ) 
;



ALTER TABLE visit ADD CONSTRAINT visit_pk PRIMARY KEY (n_visit);


ALTER TABLE visit ADD CONSTRAINT doctor_visit FOREIGN KEY (id_doctor) REFERENCES doctor (id_doctor);


ALTER TABLE doctor ADD CONSTRAINT spec_doctor FOREIGN KEY (code_spec) REFERENCES speciality (code_spec);


ALTER TABLE visit ADD CONSTRAINT srv_visit FOREIGN KEY (code_srv) REFERENCES services (code_srv);


ALTER TABLE visit ADD CONSTRAINT visit_patient FOREIGN KEY (id_patient) REFERENCES patient (n_card);

CREATE SEQUENCE p_patient_id_seq START WITH 1;