#ifndef TOY_ROBOT_MAIN_INCLUDE
#define TOY_ROBOT_MAIN_INCLUDE

#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <sstream>


using namespace std;

class InputException : public exception {
private:
	string excMessage;

public:
	InputException(const string& excMsg) : excMessage(excMsg) {}

	const char* what() const noexcept override {
		return excMessage.c_str();
	}
};

class ToyRobotMain {

public:

//Use SUCCESS for readability
	const int SUCCESS = 0;

	void runApplication();

	void processInputCommand(string inCmd);

	string trim(const string& str)
	{
		auto start = find_if_not(str.begin(), str.end(), ::isspace);
		auto end = find_if_not(str.rbegin(), str.rend(), ::isspace).base();
		return (start < end) ? string(start, end) : string();
	};

	static string getExceptionMessage();
	static void setExceptionMessage(string excMsg);

	static bool getSuccessfulRun();
	static void setSuccessfulRun(bool runResult);

private:
	static string exceptionMessage;
	static bool isSuccessfulRun;
	static exception resultException;
};

#endif


