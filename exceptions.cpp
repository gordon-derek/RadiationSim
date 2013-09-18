//Implementation File
//Author: Derek Gordon
//Date: November 14, 2011
//Purpose: To implement the methods specified in the 
//	specification file

#include "exceptions.h"
#include <iostream>



ExceptionClass::ExceptionClass()
{
}

void ExceptionClass::HandleExc(string message)
{
	cout << "Exception Raised: " << message << endl;
}

