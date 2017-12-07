/*
 * Employee.hpp
 *
 *  Created on: Nov 30, 2017
 *      Author: BryceX1
 */

#ifndef EMPLOYEE_HPP_
#define EMPLOYEE_HPP_
#include <string>

class Employee {
public:
	Employee();
	virtual ~Employee();

	int EmpID;
	std::string Name;
	int SSN;
	std::string Address;
	std::string Email;


};

#endif /* EMPLOYEE_HPP_ */
