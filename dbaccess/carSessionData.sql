drop table if exists carSessionData;
create table carSessionData (
	gameSessionId int NOT NULL,
	PRIMARY KEY (gameSessionId),
	coinTotal int,
	handCalibrationClose float(7,4),
	handCalibrationOpen float(7,4)
	);


