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

INSERT INTO User (username, password, first_name, last_name, address, city, state, zipcode, age, gender, device_id, security_question, security_answer, email) VALUES
("johndoe", "password", "John", "Doe", "103 Elm Street", "Bristow", "VA", "20136", "64", "M", "SK10430", "1", "2005", "jdoe@gmail.com"),
("maryjones", "password", "Mary", "Jones", "108 Oak Street", "Bristow", "VA", "20136", "68", "F", "SK30490", "1", "2008", "jdoe@gmail.com");

INSERT INTO Event (heart_rate, acceleration, location, resolved, user_id) VALUES 
("0", "0", "0", "0", "1");