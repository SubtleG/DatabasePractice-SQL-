//============================================================================
// Name        : Database-SQL.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <sqlite3.h>
#include "Employee.hpp"
#include "Department.hpp"
#include <sstream>
using namespace std;

static int EmpSelectCallBack(void* db, int argc, char **argv, char **colNames);
static int DeptSelectCallBack(void* db, int argc, char **argv, char **colNames);
static vector<Employee*> empVect;
static vector<Department*> deptVect;
//These might cause errors if they are not static when passing them.
void InsertEmployee(sqlite3* database);
void UpdateEmployee(sqlite3* database);
void DeleteEmployee(sqlite3* database);

int main() {
	//SQL variables
	int return_code;
	sqlite3* database;
	char *ErrMsg = 0;
	string sql;

	return_code = sqlite3_open("CompanyDB.DB", &database);
	if (return_code){
		cout << "Error opening the database" << endl;
	}
	else{
		cout << "Database opened successfully" << endl;
	}

	//Process data here
	sql = "SELECT * FROM Employee;";
	return_code = sqlite3_exec(database,
			sql.c_str(),
			EmpSelectCallBack,
			(void*)"Employee Select",
			&ErrMsg);

	sql = "SELECT * FROM Department;";
	return_code = sqlite3_exec(database,
			sql.c_str(),
			DeptSelectCallBack,
			(void*)"Department Select",
			&ErrMsg);

	//or
	//Insert new employee
	//InsertEmployee(database);

	//Update current Employee
	UpdateEmployee(database);

	//Delete single Employee
//	DeleteEmployee(database);

	//Print employee
	cout << endl;
	for (unsigned int i = 0; i < empVect.size(); i++){
		cout << setw(15) << left << "Employee Data" << endl;
		cout << setw(15) << "-------------" << endl;
		cout << setw(15) << "Name: " << empVect[i]->Name << endl;
		cout << setw(15) << "EmpID: " << empVect[i]->EmpID << endl;
		cout << setw(15) << "Email: " << empVect[i]->Email << endl;
		cout << setw(15) << "SSN: " << empVect[i]->SSN << endl;
		cout << setw(15) << "Address: " << empVect[i]->Address << endl;
		cout << endl;
	}
//
//	//Print Department
//	cout << endl;
//	for (unsigned int i = 0; i < deptVect.size(); i++){
//		cout << setw(18) << left << "Department Data" << endl;
//		cout << setw(18) << "---------------" << endl;
//		cout << setw(18) << "Name: " << deptVect[i]->Name << endl;
//		cout << setw(18) << "DeptID: " << deptVect[i]->DeptID << endl;
//		cout << setw(18) << "URL: " << deptVect[i]->URL << endl;
//		cout << endl;
//	}

	sqlite3_close(database);
	cout << "Program ending, Have a nice day!" << endl; // prints Program ending, Have a nice day!
	return 0;
}

void InsertEmployee(sqlite3* database){
	string sql;
	stringstream ss;
	int returnCode;
	char* errMsg;
//
//			"INSERT INTO Employee VALUES (001,
//			"Smith, Tammy",
//			"123456789",
//			NULL,
//			NULL,
//			NULL,
//			200);"
//

	int theID;
	cout << "Please enter an employee ID: ";
	cin >> theID;
	cin.clear();
	cin.ignore(32768, '\n');

	string theName;
	cout << "Please enter a Name: ";
	getline(cin, theName);

	int theSSN;
	cout << "Please enter an employee SSN: ";
	cin >> theSSN;
	cin.clear();
	cin.ignore(32768, '\n');

	string theEmail;
	cout << "Please enter their email address: ";
	getline(cin, theEmail);

	int theDeptID;
	cout << "Please enter a department ID: ";
	cin >> theDeptID;
	cin.clear();
	cin.ignore(32768, '\n');

	//Build up the SQL Insert statement based on user input
	ss << "INSERT INTO Employee (EmpID, Name, SSN, DeptID, Email) VALUES (";
	ss << theID << ", ";
	ss << "'" << theName << "', ";
	ss << theSSN << ", ";
	ss << theDeptID << ", ";
	ss << "'" << theEmail << "'); ";


	sql = ss.str();
//	cout << "The sql string is: " << endl;
//	cout << sql << endl;

	returnCode = sqlite3_exec(database, sql.c_str(), EmpSelectCallBack, 0, &errMsg);

	if (returnCode != SQLITE_OK){
		cout << "Error inserting: " << sql << endl;
		cout << "Error message: " << errMsg << endl;
	}
	else{
		cout << "Employee sucessfully inserted." << endl;
	}
}

void UpdateEmployee(sqlite3* database){
	string sql;
	stringstream ss;
	int returnCode;
	char* errMsg;

	int theID;
	cout << "Please enter an employee ID: ";
	cin >> theID;
	cin.clear();
	cin.ignore(32768, '\n');

	string theName;
	cout << "Please enter their changed name: ";
	getline(cin, theName);

	//Build up the SQL Insert statement based on user input
	// UPDATE Syntax error
	ss << "UPDATE Employee set Name = ";
	ss << "'" << theName << "', ";
	ss << " WHERE EmpID = ";
	ss << theID << ";";

	sql = ss.str();

	cout << "The sql string is: " << endl;
	cout << sql << endl;

	returnCode = sqlite3_exec(database, sql.c_str(), EmpSelectCallBack, 0, &errMsg);

	if (returnCode != SQLITE_OK){
		cout << "Error updating: " << sql << endl;
		cout << "Error message: " << errMsg << endl;
	}
	else{
		cout << "Employee sucessfully updated." << endl;
	}
}

void DeleteEmployee(sqlite3* database){
	string sql;
	stringstream ss;
	int returnCode;
	char* errMsg;
//
//			"INSERT INTO Employee VALUES (001,
//			"Smith, Tammy",
//			"123456789",
//			NULL,
//			NULL,
//			NULL,
//			200);"
//

	int theID;
	cout << "Please enter an employee ID to Delete: ";
	cin >> theID;
	cin.clear();
	cin.ignore(32768, '\n');

	//Build up the SQL Insert statement based on user input
	ss << "DELETE FROM Employee ";
	ss << "WHERE EmpID = ";
	ss << theID << ";";

	sql = ss.str();

//	cout << "The sql string is: " << endl;
//	cout << sql << endl;

	returnCode = sqlite3_exec(database, sql.c_str(), EmpSelectCallBack, 0, &errMsg);

	if (returnCode != SQLITE_OK){
		cout << "Error Deleting: " << sql << endl;
		cout << "Error message: " << errMsg << endl;
	}
	else{
		cout << "Employee sucessfully deleted." << endl;
	}
}

static int EmpSelectCallBack(void* db, int argc, char **argv, char **colNames){
	string nullHandler;
	Employee *tempEmp = new Employee();
	for (int i = 0; i < argc; i++){
		nullHandler = argv[i] ? argv[i] : "NULL";
		if(strcmp(colNames[i], "EmpID") == 0){
			tempEmp->EmpID = atoi(argv[i]);
		}
		else if(strcmp(colNames[i], "SSN") == 0){
			tempEmp->SSN = atoi(argv[i]);
		}
		else if(strcmp(colNames[i], "Address") == 0){
			tempEmp->Address = nullHandler;
		}
		else if(strcmp(colNames[i], "Email") == 0){
			tempEmp->Email = nullHandler;
		}
		else if(strcmp(colNames[i], "Name") == 0){
			tempEmp->Name = nullHandler;
		}
		else if(strcmp(colNames[i], "Photo") == 0){
			//cout << "photo" << endl;
			break;
		}
		else{
			cout << "Error in EmpSelectCallBack" << endl;
		}
		//cout << colNames[i] << "= " << nullHandler << endl;
	}
	empVect.push_back(tempEmp);
	//Probably have a memory leak here
	//cout << endl;
	return 0;
}

static int DeptSelectCallBack(void* db, int argc, char **argv, char **colNames){
	string nullHandler;
	Department *tempDept = new Department();
	for (int i = 0; i < argc; i++){
		nullHandler = argv[i] ? argv[i] : "NULL";
		if(strcmp(colNames[i], "URL") == 0){
			tempDept->URL = nullHandler;
		}
		else if(strcmp(colNames[i], "Name") == 0){
			tempDept->Name = nullHandler;
		}
		else if(strcmp(colNames[i], "DeptID") == 0){
			tempDept->DeptID = atoi(argv[i]);
		}
		else{
			cout << "Error in EmpSelectCallBack" << endl;
		}
			//cout << colNames[i] << "= " << nullHandler << endl;
	}
	deptVect.push_back(tempDept);
	//Check for memory leak
	//cout << endl;
	return 0;
}
