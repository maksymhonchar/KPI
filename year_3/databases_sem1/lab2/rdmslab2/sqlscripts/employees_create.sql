CREATE TABLE Employees (
	Id INT PRIMARY KEY AUTO_INCREMENT,
	FullName VARCHAR(255) NOT NULL,
	Characteristics TEXT NOT NULL,
	IsIntern BIT NOT NULL DEFAULT 0
);