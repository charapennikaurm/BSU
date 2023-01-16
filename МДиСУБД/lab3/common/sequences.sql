-- последовательность для генерации ключей таблицы Speciality
CREATE SEQUENCE seq_spec
  START WITH 1401
  MAXVALUE 1755;
  
-- последовательность для генерации ключей таблицы Doctor
CREATE SEQUENCE  seq_doc
  MINVALUE 1 MAXVALUE 999 INCREMENT BY 1 START WITH 11 CACHE 20 no CYCLE ;
  
-- последовательность для генерации ключей таблицы Services
CREATE SEQUENCE seq_srv
  START WITH 110
  MAXVALUE 990
  increment by 10;
  
-- последовательность для генерации ключей таблицы Patient
-- (участок 1)
CREATE SEQUENCE seq_patient_1 
  START WITH 116001
  MAXVALUE 116999
  increment by 1; 
-- последовательность для генерации ключей таблицы Patient
-- (участок 2)
CREATE SEQUENCE seq_patient_2
  START WITH 216001
  MAXVALUE 216999
  increment by 1;

-- последовательность для генерации ключей таблицы Visit
CREATE SEQUENCE  seq_visit
  MINVALUE 1 INCREMENT BY 1 CACHE 20 no CYCLE ;

