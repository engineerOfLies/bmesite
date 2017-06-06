drop table if exists carGameData;
create table carGameData (
	gameSessionId int NOT NULL,
	timestamp time(3) NOT NULL,
	PRIMARY KEY (gameSessionId,timestamp),
	opening float (7,4),
	carSpeed float(7.4),
	carFlipped bool,
	palmRoll float(7,4),
	coinsCollected int
	);

