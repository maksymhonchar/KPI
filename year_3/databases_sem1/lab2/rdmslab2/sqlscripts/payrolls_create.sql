CREATE TABLE Payrolls (
	Id INT NOT NULL AUTO_INCREMENT,
	EmployeeId INT NOT NULL,
	PaymentId INT NOT NULL,
	ProjectId INT NOT NULL,
	PayrollDate DATE NOT NULL,
	PRIMARY KEY (Id, EmployeeId, PaymentId, ProjectId),
	CONSTRAINT FK_Employee FOREIGN KEY (EmployeeId) REFERENCES Employees(Id),
	CONSTRAINT FK_Payment FOREIGN KEY (PaymentId) REFERENCES Payments(Id),
	CONSTRAINT FK_Project FOREIGN KEY (ProjectId) REFERENCES Projects(Id)
);