USE r4rmusic1_development;
DROP TABLE IF EXISTS works;
DROP TABLE IF EXISTS editions;
DROP TABLE IF EXISTS composers;
CREATE TABLE works (
    id INT(11) NOT NULL AUTO_INCREMENT,
    composer_id INT(11),
    title VARCHAR(100),
    PRIMARY KEY (id)
);
CREATE TABLE editions (
    id INT(11) NOT NULL AUTO_INCREMENT,
    work_id INT(11) NOT NULL,
    description VARCHAR(30),
    publisher VARCHAR(60),
    year INT(4),
    price FLOAT,
    PRIMARY KEY (id)
);
CREATE TABLE composers (
    id INT(11) NOT NULL AUTO_INCREMENT,
    first_name VARCHAR(25),
    last_name VARCHAR(25),
    PRIMARY KEY (id)
);
