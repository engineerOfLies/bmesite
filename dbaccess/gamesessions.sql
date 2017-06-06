drop table if exists gameSessions;
create table gameSessions (
	gameSessionId int NOT NULL AUTO_INCREMENT,
	PRIMARY KEY (gameSessionId),
	patientId int NOT NULL,
	gameId int NOT NULL,
	therapistPresent BOOL,
	startTime bigint,
	endtime bigint
);

