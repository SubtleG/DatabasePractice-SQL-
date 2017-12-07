/*
 * Department.hpp
 *
 *  Created on: Nov 30, 2017
 *      Author: BryceX1
 */

#ifndef DEPARTMENT_HPP_
#define DEPARTMENT_HPP_
#include <string>

class Department {
public:
	Department();
	virtual ~Department();


	std::string Name;
	std::string URL;
	int DeptID;
};

#endif /* DEPARTMENT_HPP_ */
