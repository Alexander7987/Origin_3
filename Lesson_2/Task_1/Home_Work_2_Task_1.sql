--Сначала отдельно создали таблицу Жанров с обязательным ограничением целостности primary key для дальнейшего использования references
CREATE TABLE IF NOT EXISTS Genre (
	Name text primary key
);


--Затем отдельно создали таблицу Певцов с обязательным ограничением целостности primary key для дальнейшего использования references
CREATE TABLE IF NOT EXISTS Singer (
	Pseudonym text primary key
);


--После написали симбиоз двух таблиц Певцов и Жанров, показывая разносторонность певцов. Это вариант "многие ко многим"
CREATE TABLE IF NOT EXISTS Singer_Genre (
	Pseudonym_name text not null references Singer(Pseudonym),
	Genre_name text not null references Genre(Name),
	constraint pk UNIQUE (Pseudonym_name, Genre_name) -- чтобы не было повторений комбинаций
);


---------------------------------------------------------
--Сначала отдельно создали таблицу Альбомов с обязательным ограничением целостности primary key для дальнейшего использования references
CREATE TABLE IF NOT EXISTS Albums (
	Name text primary key,
	Year date
);


--После написали симбиоз двух таблиц Альбомов и Певцов, показывая разносторонность.  Это вариант "многие ко многим"
CREATE TABLE IF NOT EXISTS Albums_Singer (
	Album_name text not null references Albums(Name),
	Pseudonym_name text not null references Singer(Pseudonym),
	constraint pkk UNIQUE (Album_name, Pseudonym_name) -- чтобы не было повторений комбинаций
);

------------------------------------------------------------------------------------------------------
-- Симбиоз Трека и Альбома, только каждый трек принадлежит строго одному альбому.  Это вариант "один ко многим"
CREATE TABLE IF NOT EXISTS Tracks (
	Name text primary key,
	Time integer,
	Album_name text not null references Albums(Name),
	constraint pkkk UNIQUE (Name, Album_name) -- чтобы не было повторений комбинаций
);
-------------------------------------------------------------------------------------------------------

--Сначала отдельно создали таблицу Сборников с обязательным ограничением целостности primary key для дальнейшего использования references
create table if not exists Collections (
    Name text primary key,
    Year date
);


--После написали симбиоз двух таблиц Коллекций и Треков, показывая разносторонность.  Это вариант "многие ко многим"
create table if not exists Collections_Tracks (
    Collections_name text not null references Collections(Name),
	Tracks_name text not null references Tracks(Name),
	constraint pkkkkk UNIQUE (Collections_name, Tracks_name) -- чтобы не было повторений комбинаций
);
