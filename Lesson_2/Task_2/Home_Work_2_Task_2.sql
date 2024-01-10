create table if not exists Employee (
id_employee integer primary key,
Name text UNIQUE,
Department text,
id_chief integer references Employee(id_employee) --не пишем not null, т.к. может быть и равен нулю
);