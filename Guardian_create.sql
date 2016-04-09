#DB Creation Script for Guardian Project

DROP TABLE IF EXISTS User, Event;

CREATE TABLE User
(
    id INT NOT NULL AUTO_INCREMENT,
    username VARCHAR (32) NOT NULL,
    password VARCHAR (256) NOT NULL,
    first_name VARCHAR (32) NOT NULL,
    last_name VARCHAR (32) NOT NULL,
    address VARCHAR (255) NOT NULL,
    city VARCHAR (255) NOT NULL,
    state VARCHAR (32) NOT NULL,
    zipcode INT NOT NULL,
    age INT NOT NULL, 
    gender VARCHAR(1) NOT NULL, 
    device_id VARCHAR(255) NOT NULL, 
    security_question INT,
    security_answer VARCHAR (255),
    email VARCHAR(64),      
    PRIMARY KEY (id)
);

CREATE TABLE Event
(
       id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT NOT NULL,
       heart_rate INT, 
       acceleration INT, 
       location INT,
       resolved INT, 
       user_id INT,
       FOREIGN KEY (user_id) REFERENCES User(id) ON DELETE CASCADE
);