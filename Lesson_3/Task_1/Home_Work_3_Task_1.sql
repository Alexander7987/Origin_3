INSERT INTO singer(pseudonym) 
VALUES('Sharon Kovacs'),
('Sting'),
('Hozier'),
('Celentano');


INSERT INTO genre(name) 
VALUES('Pop music'),
('Fusion'),
('Hip-Hop/Rap'),
('Electronic'),
('Rock');

INSERT INTO albums (name, year) 
VALUES('Album1', '2017-09-30'),
('Album2', '2018-06-27'),
('Album3', '2019-04-25'),
('Album4', '2019-08-16'),
('Album5', '2020-02-13'),
('Album6', '2021-12-29');


INSERT INTO tracks (name, time, album_name) --time в секундах
VALUES('My_Track1', 220, 'Album1'),
('Track2', 180, 'Album2'),
('Track3', 150, 'Album2'),
('Track4', 240, 'Album3'),
('My_Track5', 250, 'Album3'),
('Track6', 210, 'Album4'),
('Track7', 190, 'Album5'),
('Track8', 215, 'Album6'),
('Track9', 150, 'Album1');


INSERT INTO collections (name, year) 
VALUES('Collection1', '2017-10-27'),
('Collection2', '2018-08-22'),
('Collection3', '2019-09-28'),
('Collection4', '2020-07-19');


INSERT INTO singer_genre (pseudonym_name, genre_name) 
VALUES('Sharon Kovacs', 'Pop music'),
('Sting', 'Pop music'),
('Sting', 'Hip-Hop/Rap'),
('Hozier', 'Pop music'),
('Hozier', 'Fusion'),
('Celentano', 'Pop music');



INSERT INTO albums_singer (album_name, pseudonym_name) 
VALUES('Album1', 'Sharon Kovacs'),
('Album1', 'Sting'),
('Album2', 'Sting'),
('Album2', 'Hozier'),
('Album3', 'Celentano'),
('Album4', 'Hozier'),
('Album5', 'Sting'),
('Album5', 'Celentano'),
('Album6', 'Sharon Kovacs'),
('Album6', 'Celentano'),
('Album6', 'Hozier');


INSERT INTO collections_tracks (collections_name, tracks_name) 
VALUES('Collection1', 'My_Track1'),
('Collection1', 'Track2'),
('Collection2', 'Track2'),
('Collection2', 'Track3'),
('Collection2', 'Track4'),
('Collection2', 'My_Track1'),
('Collection3', 'Track3'),
('Collection3', 'My_Track5'),
('Collection3', 'Track6'),
('Collection4', 'Track7'),
('Collection4', 'Track8'),
('Collection4', 'My_Track1'),
('Collection4', 'My_Track5');