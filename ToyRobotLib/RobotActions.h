#ifndef ROBOT_ACTIONS_INCLUDE
#define ROBOT_ACTIONS_INCLUDE

#include <string>
#include <stdexcept>
#include <map>

using namespace std;

class ActionException : public exception {
private:
	string excMessage;

public:
	ActionException(const string& excMsg) : excMessage(excMsg) {}

	const char* what() const noexcept override {
		return excMessage.c_str();
	}
};

class RobotActions {

public:

	//Use SUCCESS for readability
	const int SUCCESS = 0;

	enum class Commands {
		PLACE,
		MOVE,
		LEFT,
		RIGHT,
		REPORT
	};

	enum class Directions {
		NORTH,
		EAST,
		SOUTH,
		WEST
	};

	map<string, int> posIdx =
	{
		{"X_AXIS", 0},
		{"Y_AXIS", 1},
		{"DIRECTION", 2}
	};

	int validateCommand(string cmd, exception& e, Commands& cmdEnum);
	int validatePosition(string params, int position[1][3], exception& e);

	void setXPosition(int pos, int currentPosition[1][3]) { currentPosition[0][posIdx["X_AXIS"]] = pos; };
	void setYPosition(int pos, int currentPosition[1][3]) { currentPosition[0][posIdx["Y_AXIS"]] = pos; };
	void setDirection(int dir, int currentPosition[1][3]) { currentPosition[0][posIdx["DIRECTION"]] = dir; };

	int getXPosition() { return reportPosition[0][posIdx["X_AXIS"]]; };
	int getYPosition() { return reportPosition[0][posIdx["Y_AXIS"]]; };
	int getDirection() { return reportPosition[0][posIdx["DIRECTION"]]; };

	bool isPositionValid(int position[1][3]);

	static void setIsRobotPlaced(bool isPlacedFlag);
	static bool getIsRobotPlaced();

	static void setReportPosition(int currentPosition[1][3]);
	static void getReportPosition(int currentPosition[1][3]);

	int place(int currentPosition[1][3], exception& e);
	int move(exception& e);
	int left(exception& e);
	int right(exception& e);
	int report(exception& e);

private:

	static int reportPosition[1][3];
	static bool isRobotPlaced;
};

#endif
