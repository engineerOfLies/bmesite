drop table if exists therapists;
create table therapists(
	therapistId int not null primary key,
	patientId int not null
);
