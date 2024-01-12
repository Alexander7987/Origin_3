-- Задание 2
select name, time from tracks
where time = (select MAX(time) from tracks);


select name, time from tracks
where time >= 210;

select name, year from collections
where year BETWEEN '2018-01-01' and '2020-01-01';


select pseudonym from singer
where pseudonym not like '% %';

select name from tracks
where name like '%My%';


-- Задание 3
select genre_name, count(pseudonym_name) from singer_genre -- можно написать и count(pseudonym_name)
group by genre_name;

select COUNT(*) from tracks
join albums on tracks.album_name = albums.name
where albums.year between '2019-01-01' and '2020-12-31';


select distinct pseudonym_name from albums_singer
join albums on albums.name = albums_singer.album_name
where year not between '2020-01-01' and '2020-12-31';

select distinct collections.name from collections
join collections_tracks a on collections.name = a.collections_name
join tracks b on a.tracks_name = b.name
join albums_singer c on b.album_name = c.album_name
where c.pseudonym_name = 'Sharon Kovacs';

-- Задание 4
select distinct album_name from albums_singer
join singer_genre on albums_singer.pseudonym_name = singer_genre.pseudonym_name
group by album_name, singer_genre.pseudonym_name --группируем по двум полям, т.к. альбом+певец могут повторятся. Если таких пар несколько, то это значит, что исполнитель играет больше, чем в 1 жанре
having 1 < count(genre_name)
order by album_name;


select name from tracks
left join collections_tracks on tracks.name = collections_tracks.tracks_name
where collections_tracks.collections_name is null;


select distinct pseudonym_name, time from albums_singer
join tracks on albums_singer.album_name = tracks.album_name
where time = (select MIN(time) from tracks);


select album_name, count(*) from tracks
group by album_name
having count(*) = (select count(*) from tracks
                   group by album_name
                   order by count(*) asc 
                   limit 1);





