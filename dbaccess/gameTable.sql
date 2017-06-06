drop table if exists gameTable;
create table gameTable (
	gameId int NOT NULL AUTO_INCREMENT,
	PRIMARY KEY (gameId),
	name VARCHAR(255) NOT NULL,
	description VARCHAR(512) NOT NULL,
	customDataTable VARCHAR(255) NOT NULL,
	customSessionTable VARCHAR(255) NOT NULL
);

