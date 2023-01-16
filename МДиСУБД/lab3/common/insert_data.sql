-- Добавление данных Специальности
insert into speciality(code_spec, title) values(nextval('seq_spec'), 'Терапевт');
insert into speciality(code_spec, title) values(nextval('seq_spec'), 'Хирург');
insert into speciality(code_spec, title) values(nextval('seq_spec'), 'Невролог');
insert into speciality(code_spec, title) values(nextval('seq_spec'), 'Офтальмолог');
insert into speciality(code_spec, title) values(nextval('seq_spec'), 'Травмвматолог');
insert into speciality(code_spec, title) values(nextval('seq_spec'), 'Дерматовенеролог');
insert into speciality(code_spec, title) values(nextval('seq_spec'), 'Медсестра');
insert into speciality(code_spec, title) values(nextval('seq_spec'), 'Интерн');
insert into speciality(code_spec, title) values(nextval('seq_spec'), 'Кардиолог');

-- Добавление данных Врачи
INSERT INTO doctor(id_doctor, surname, first_name, middle_name, code_spec) VALUES(nextval('seq_doc'), 'Быков', 'Андрей', 'Евгеньевич', 1401);
INSERT INTO doctor(id_doctor, surname, first_name, middle_name, code_spec) VALUES(nextval('seq_doc'), 'Кисегач', 'Анастасия', 'Константиновна', 1401);
INSERT INTO doctor(id_doctor, surname, first_name, middle_name, code_spec) VALUES(nextval('seq_doc'), 'Купитман', 'Иван', 'Натанович', 1406);
INSERT INTO doctor(id_doctor, surname, first_name, middle_name, code_spec) VALUES(nextval('seq_doc'), 'Королева', 'Маргарита', 'Павловна', 1407);
INSERT INTO doctor(id_doctor, surname, first_name, middle_name, code_spec) VALUES(nextval('seq_doc'), 'Левин', 'Борис', 'Аркадьевич', 1404);
INSERT INTO doctor(id_doctor, surname, first_name, middle_name, code_spec) VALUES(nextval('seq_doc'), 'Черноус', 'Варвара', 'Николаевна', 1408);
INSERT INTO doctor(id_doctor, surname, first_name, middle_name, code_spec) VALUES(nextval('seq_doc'), 'Романенко', 'Глеб', 'Викторович', 1401);
INSERT INTO doctor(id_doctor, surname, first_name, middle_name, code_spec) VALUES(nextval('seq_doc'), 'Лобанов', 'Семен', 'Семенович', 1408);
INSERT INTO doctor(id_doctor, surname, first_name, middle_name, code_spec) VALUES(nextval('seq_doc'), 'Ричардс', 'Фил', NULL, 1406);
INSERT INTO doctor(id_doctor, surname, first_name, middle_name, code_spec) VALUES(nextval('seq_doc'), 'Ульянова', 'Полина', 'Сергеевна', 1408);
INSERT INTO doctor(id_doctor, surname, first_name, middle_name, code_spec) VALUES(nextval('seq_doc'), 'Корнеев', 'Максим', 'Леонидович', 1402);
INSERT INTO doctor(id_doctor, surname, first_name, middle_name, code_spec) VALUES(nextval('seq_doc'), 'Калинина', 'Софья', 'Яковлевна ', 1405);

-- Добавление данных Пациенты
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_1'),'Безенчук', 'Федор', 'Николаевич', 'г. Артемовск', '+375256788098');
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_2'),'Берлага', 'Михаил', 'Александрович','г. Южногорск', '+375331234579');
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_1'),'Грицацуева', 'Нина', 'Ивановна','г. Прокопьевск', '+375299089096');
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_1'),'Паниковский', 'Самюэль','Михайлович', 'г. Криворуков', '+375244777881');
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_1'),'Христофоров', 'Эрнест', 'Ричардович','г. Бердянск', '+375991456682');
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_2'),'Щукина', 'Элла', 'Аркадьевна','г. Урюпинск', '+375113451173');
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_1'),'Бендер', 'Остап', 'Ибрагимович','г. Черноморск', '+375000000000');
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_1'),'Балаганов', 'Александр', 'Николаевич', 'г. Черноморск', '+375444567799');
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_1'),'Корейко', 'Александр', 'Иванович','г. Урюпинск', '+375337777777');
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_1'),'Козлевич','Адам', 'Казимирович', 'г. Верхнехолмск', '+375172061544');
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_2'),'Растопыркин ', 'Григорий', 'Феликсович','г. Урюпинск', '+375173076553');
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_2'),'Рукоблудов', 'Леонид', 'Ильич', 'г. Криворуков', '+375172061544' );
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_2'),'Филинов', 'Василий', 'Денисович', 'г. Артемовск', '+375552347890');
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_2'),'Тугодумов', 'Василий', 'Федорович', 'г. Верхнехолмск', '+375297777777');
INSERT INTO patient(n_card, surname, first_name, middle_name, address, phone) VALUES(nextval('seq_patient_2'),'Заныкин', 'Андрей', 'Данилович', 'г. Артемовск', '+375172124689');

-- Добавление данных Услуги
INSERT INTO services(code_srv, title, price) VALUES(nextval('seq_srv'), 'Консультация', 50.00);
INSERT INTO services(code_srv, title, price) VALUES(nextval('seq_srv'), 'Первичный осмотр', 15.30);
INSERT INTO services(code_srv, title, price) VALUES(nextval('seq_srv'), 'Рефлексотерапия', 185.60);
INSERT INTO services(code_srv, title, price) VALUES(nextval('seq_srv'), 'Физиолечение', 5.30);
INSERT INTO services(code_srv, title, price) VALUES(nextval('seq_srv'), 'Курс терапевтического лечения', 47.75);
INSERT INTO services(code_srv, title, price) VALUES(nextval('seq_srv'), 'Курс профилактического лечения', 300.00);
INSERT INTO services(code_srv, title, price) VALUES(nextval('seq_srv'), 'Ренгеноскопия', 10.00);
INSERT INTO services(code_srv, title, price) VALUES(nextval('seq_srv'), 'ЭКГ', 0.85);
INSERT INTO services(code_srv, title, price) VALUES(nextval('seq_srv'), 'Компьютерная томография', 450.99);
INSERT INTO services(code_srv, title, price) VALUES(nextval('seq_srv'), 'МРТ', 560.70);
INSERT INTO services(code_srv, title, price) VALUES(nextval('seq_srv'), 'Анализ крови', 0.35);

-- Добавление данных Визиты
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 13, 116002, '2022-09-12'::date, 110);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 21, 116003, '2022-09-12'::date, 110);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 11, 216002, '2022-09-12'::date, 150);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 20, 116006, '2022-09-13'::date, 160);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 18, 216003, '2022-09-13'::date, 120);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 11, 116007, '2022-09-14'::date, 150);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 20, 216004, '2022-09-15'::date, 160);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 14, 116008, '2022-09-19'::date, 210);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 19, 216001, '2022-09-19'::date, 170);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 21, 116003, '2022-09-19'::date, 110);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'),NULL,216005, '2022-09-20'::date, 170);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 18, 216002, '2022-09-21'::date, 140);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 16, 116004, '2022-09-21'::date, 110);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 18, NULL,   '2022-09-22'::date, 120);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), NULL,216001,'2022-09-23'::date, 210);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 22, 216007, '2022-09-26'::date, 130);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 21, 116003, '2022-09-26'::date, 110);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), NULL,216001,'2022-09-27'::date, 170);
INSERT INTO visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 22, 116008, '2022-09-28'::date, 130);
INSERT into visit (n_visit, id_doctor, id_patient, visit_date, code_srv) VALUES (nextval('seq_visit'), 12, 116007, '2022-09-29'::date, 200);