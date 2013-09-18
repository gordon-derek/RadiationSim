//Specification File
//Author: Derek Gordon
//Date: November 14, 2011
//Purpose: To print statements to the screen(or file) corrosponding
//		with the error that has been sent into the class.

#include <string>
using namespace std;

class ExceptionClass
{
public:
		ExceptionClass();//default constructor, does nothing

		void HandleExc(string message);
		//Pre: An exception has been thrown by the class
		//Post: An output has been printed to the screen(or file)
		//Purpose: To notify the user that an exception has occurred

private:

};//end ExceptionClass
	