create table if not exists Chief (
Name text primary key,
Department text
);


--У начальника может быть несколько подчиненных, поэтому здесь связь "один ко многим"
create table if not exists Employee (
Name text UNIQUE,
Department text,
Chief_name text not null references Chief(Name)
);