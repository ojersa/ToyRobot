#include "ToyRobotMain.h"
#include "RobotActions.h"

using namespace std;

//Defines the valid input commands
map<string, RobotActions::Commands> commandMap =
{
	{"PLACE", RobotActions::Commands::PLACE},
	{"MOVE", RobotActions::Commands::MOVE},
	{"LEFT", RobotActions::Commands::LEFT},
	{"RIGHT", RobotActions::Commands::RIGHT},
	{"REPORT", RobotActions::Commands::REPORT}
};

//Defines the valid input directions
map<std::string, RobotActions::Directions> directionMap =
{
	{"NORTH", RobotActions::Directions::NORTH},
	{"EAST", RobotActions::Directions::EAST},
	{"SOUTH", RobotActions::Directions::SOUTH},
	{"WEST", RobotActions::Directions::WEST}
};

/**
 * @brief Validates a command string and updates the corresponding command enumeration and exception.
 *
 * This function checks if the provided command string is valid as defined in the commandMap
 * and sets the appropriate ommand enumeration value.
 * If the command is invalid, it populates the provided exception object with an error message.
 *
 * @param cmd The command string to validate.
 * @param e Reference to an exception object that will be populated with an error message if
 *		the command is invalid.
 * @param cmdEnum Reference to a Commands enumeration that will be updated with the
 *		corresponding command value if the command is valid.
 * @return true if the command is valid, false otherwise.
 */
int RobotActions::validateCommand(string cmd, exception& e, Commands& cmdEnum)
{
	auto it = commandMap.find(cmd);
	if (it != commandMap.end())
	{
		cmdEnum = it->second;
	}
	else
	{
		throw ActionException("Invalid command!");
	}

	return SUCCESS;
}

/**
 * @brief Checks if a given position is valid within a specified range.
 *
 * This function validates the position provided in a 1x3 integer array.
 * A valid position should have a format of x,y,f
 *		x - INTEGER[0-5]
 *		y - INTEGER[0-5]
 *		f - DIRECTION[0(NORTH), (1)EAST, (2)SOUTH, (3)WEST]
 *
 * @param position A 1x3 array containing position coordinates to validate.
 * @return true if the position is valid, false otherwise.
 */
bool RobotActions::isPositionValid(int position[1][3])
{
	int limits[1][3] = { {5, 5, 3} };

	for (int j = 0; j < 3; ++j)
	{
		if (position[0][j] > limits[0][j] || position[0][j] < 0)
		{
			return false;
		}
	}

	return true;
}

/**
 * @brief Validates the given position based on input parameters.
 *
 * This function takes a string of parameters and a 1x3 integer array representing
 * a position. It checks if the position is valid based on the parameters and
 * populates an exception object with an error message if validation fails.
 *
 * @param inPos A string containing the position coordinates to validate.
 * A valid inPos should have a format of x,y,f
 *		x - INTEGER[0-5]
 *		y - INTEGER[0-5]
 *		f - DIRECTION[NORTH, EAST, SOUTH, WEST]
 * @param position Reference to a 1x3 array that will be populated if inPos is valid.
 * @param e Reference to an exception object that will be populated with an
 *           error message if the position is invalid.
 * @return true if the position is valid, false otherwise.
 */
int RobotActions::validatePosition(string inPos, int position[1][3], exception& e)
{
	stringstream input(inPos);
	string unit;
	vector<string> units;

	while (getline(input, unit, ','))
	{
		// Trim leading and trailing whitespace
		unit.erase(0, unit.find_first_not_of(' ')); // trim left
		unit.erase(unit.find_last_not_of(' ') + 1); // trim right
		units.push_back(unit);
	}

	//Parsed command and parameters, validate
	int xPos;
	int yPos;
	int dir;

	//Check the number of inputs
	if (units.size() != 3)
	{
		throw ActionException("Invalid position!");
	}

	//Check if x position is a number
	try
	{
		xPos = stoi(units[posIdx["X_AXIS"]]);
	}
	catch (...)
	{
		throw ActionException("Invalid x position!");
	}

	//Check if y position is a number
	try
	{
		yPos = stoi(units[posIdx["Y_AXIS"]]);
	}
	catch (...)
	{
		throw ActionException("Invalid y position!");
	}

	//Check if valid direction
	auto it = directionMap.find(units[posIdx["DIRECTION"]]);
	if (it != directionMap.end())
	{
		dir = static_cast<int>(it->second);
	}
	else
	{
		throw ActionException("Invalid Direction!");
	}

	//Now assigning to position matrix
	setXPosition(xPos, position);
	setYPosition(yPos, position);
	setDirection(dir, position);

	//Check if within limits
	if (!isPositionValid(position))
	{
		throw ActionException("Position over the limit!");
	}

	return SUCCESS;
}

int RobotActions::reportPosition[1][3] = { {0, 0, 0} };
bool RobotActions::isRobotPlaced = false;

/**
 * @brief Sets the placement status of the robot.
 *
 * This function updates the flag indicating whether the robot
 * has been placed in a valid position on the table.
 *
 * @param isPlacedFlag A boolean value indicating if the robot is
 *						currently placed (true) or not (false).
 *						This flag will later help ensure that robot
 *						 was placed before calling other commands.
 */
void RobotActions::setIsRobotPlaced(bool isPlacedFlag)
{
	isRobotPlaced = isPlacedFlag;
}

/**
 * @brief Retrieves the current placement status of the robot.
 *
 * This function returns a boolean value indicating whether the robot
 * is currently placed in a valid position on the table
 *
 * @return true if the robot is placed, false otherwise.
 *						This flag will later help ensure that robot
 *						 was placed before calling other commands.
 */
bool RobotActions::getIsRobotPlaced()
{
	return isRobotPlaced;
}

/**
 * @brief Sets the robot's current position.
 *
 * This function updates the robot's position coordinates based on
 * the values provided in the input array. The coordinates should
 * represent the robot's location withintable.
 *
 * @param currentPosition A 1x3 array containing the new position
 *                       coordinates (x, y, f) to be set for the robot.
 */
void RobotActions::setReportPosition(int currentPosition[1][3])
{
	for (int j = 0; j < 3; ++j)
	{
		reportPosition[0][j] = currentPosition[0][j];
	}
}

/**
 * @brief Retrieves the current position of the robot.
 *
 * This function fills the provided 1x3 integer array with the robot's
 * current position coordinates. The coordinates represent the robot's
 * location within the table.
 *
 * @param currentPosition A 1x3 array that will be populated with the
 *                       robot's current position (x, y, f).
 */

void RobotActions::getReportPosition(int currentPosition[1][3])
{
	for (int j = 0; j < 3; ++j)
	{
		currentPosition[0][j] = reportPosition[0][j];
	}
}

/**
 * @brief Places the robot at the specified position.
 *
 * This function attempts to place the robot at the coordinates provided
 * in the currentPosition array. If the placement is successful, the
 * function returns a status code indicating success. If the placement
 * fails (e.g., due to an invalid position), it populates the exception
 * object with an appropriate error message.
 *
 * @param currentPosition A 1x3 array containing the position coordinates
 *                       (x, y, f) where the robot should be placed.
 * @param e Reference to an exception object that will be populated with an
 *           error message if the placement fails.
 * @return 0 if the action is successful, a non-zero error code otherwise.
 */
int RobotActions::place(int currentPosition[1][3], exception& e)
{
	if (!isPositionValid(currentPosition))
	{
		throw ActionException("Cannot place here!");
	}

	setIsRobotPlaced(true);
	setReportPosition(currentPosition);

	return SUCCESS;
}


/**
 * @brief Moves the robot one unit towards the direction it is facing.
 *
 * This function updates the robot's coordinates if new position is valid.
 *		NORTH - add 1 to the y position
 *		SOUTH - deduct 1 from the y position
 *		EAST - add 1 to the x position
 *		SOUTH - deduct 1 from the y position
 *
 * If the move is not valid (beyond the 5x5 table), it populates the
 * exception object with an error message indicating the reason for the failure.
 * Position will remain the same.
 *
 * This funtion cannot be called if RobotActions::place was not initially called.
 *
 * @param e Reference to an exception object that will be populated with
 *           an error message if the move is invalid.
 * @return 0 if the action is successful, a non-zero error code otherwise.
 */
int RobotActions::move(exception& e)
{
	if (!getIsRobotPlaced())
	{
		throw ActionException("Cannot MOVE before PLACE!");
	}

	int currPosition[1][3];
	setXPosition(getXPosition(), currPosition);
	setYPosition(getYPosition(), currPosition);
	setDirection(getDirection(), currPosition);

	Directions currDirection = static_cast<Directions>(getDirection());

	switch (currDirection)
	{
	case RobotActions::Directions::NORTH:
		currPosition[0][posIdx["Y_AXIS"]]++;
		break;
	case RobotActions::Directions::EAST:
		currPosition[0][posIdx["X_AXIS"]]++;
		break;
	case RobotActions::Directions::SOUTH:
		currPosition[0][posIdx["Y_AXIS"]]--;
		break;
	case RobotActions::Directions::WEST:
		currPosition[0][posIdx["X_AXIS"]]--;
		break;
	default:
		throw ActionException("Invalid Direction!");
		break;
	}

	if (!isPositionValid(currPosition))
	{
		throw ActionException("Cannot MOVE here!");
	}

	setReportPosition(currPosition);
	return SUCCESS;
}

/**
 * @brief Rotates the robot 90 degrees to the left.
 *
 * This function updates the robot's facing direction to reflect a 90-degree
 * rotation to the left (counter-clockwise). If the rotation is
 * successful, it updates the robot's direction.
 *
 * If the action is not valid, it populates the
 * exception object with an error message indicating the reason for the failure.
 * Facing direction will remain the same.
 *
 * This funtion cannot be called if RobotActions::place was not initially called.
 *
 * @param e Reference to an exception object that will be populated with
 *           an error message if the rotation fails.
 * @return 0 if the action is successful, a non-zero error code otherwise.
 */
int RobotActions::left(exception& e)
{
	if (!getIsRobotPlaced())
	{
		throw ActionException("Cannot ROTATE LEFT before PLACE!");
	}

	int currentPosition[1][3];
	string direction;

	getReportPosition(currentPosition);
	int currentDir = getDirection();
	currentDir = (currentDir + 3) % 4;

	setDirection(currentDir, currentPosition);
	setReportPosition(currentPosition);

	return SUCCESS;
}

/**
 * @brief Rotates the robot 90 degrees to the right.
 *
 * This function updates the robot's facing direction to reflect a 90-degree
 * rotation to the right (clockwise). If the rotation is
 * successful, it updates the robot's direction.
 *
 * If the action is not valid, it populates the
 * exception object with an error message indicating the reason for the failure.
 * Facing direction will remain the same.
 *
 * This funtion cannot be called if RobotActions::place was not initially called.
 *
 * @param e Reference to an exception object that will be populated with
 *           an error message if the rotation fails.
 * @return 0 if the action is successful, a non-zero error code otherwise.
 */
int RobotActions::right(exception& e)
{
	if (!getIsRobotPlaced())
	{
		throw ActionException("Cannot ROTATE RIGHT before PLACE!");
	}

	int currentPosition[1][3];
	string direction;

	getReportPosition(currentPosition);
	int currentDir = getDirection();
	currentDir = (currentDir + 1) % 4;

	setDirection(currentDir, currentPosition);
	setReportPosition(currentPosition);

	return SUCCESS;
}

/**
 * @brief Diplays the robot's current position.
 *
 * This function will retrieve the robot's current and display as format:
 * Output: x,y,f
 *
 * If the action is not valid, it populates the
 * exception object with an error message indicating the reason for the failure.
 *
 * This funtion cannot be called if RobotActions::place was not initially called.
 *
 * @param e Reference to an exception object that will be populated with
 *           an error message if the rotation fails.
 * @return 0 if the action is successful, a non-zero error code otherwise.
 */
int RobotActions::report(exception& e)
{
	if (!getIsRobotPlaced())
	{
		throw ActionException("Cannot REPORT before PLACE!");
	}

	int currentPosition[1][3];
	string direction;
	getReportPosition(currentPosition);

	Directions value = static_cast<Directions>(getDirection());

	for (const auto& pair : directionMap)
	{
		if (pair.second == value)
		{
			direction = pair.first;
		}
	}

	cout << "Output: " << getXPosition() << ",";
	cout << getYPosition() << ",";
	cout << direction << endl;

	return SUCCESS;
}