#include "ToyRobotMain.h"
#include "RobotActions.h"
#include "pch.h"

using namespace std;

string ToyRobotMain::exceptionMessage;
bool ToyRobotMain::isSuccessfulRun = false;

string ToyRobotMain::getExceptionMessage()
{
	return exceptionMessage;
}

void ToyRobotMain::setExceptionMessage(string excMsg)
{
	exceptionMessage = excMsg;
}

bool ToyRobotMain::getSuccessfulRun()
{
	return isSuccessfulRun;
}

void ToyRobotMain::setSuccessfulRun(bool runResult)
{
	isSuccessfulRun = runResult;
}

void ToyRobotMain::processInputCommand(string inCmd)
{
	try
	{
		if (trim(inCmd).empty())
		{
			throw InputException("Empty user input!");
		}
		else
		{

			//Parsing the command and position from the input string
			//These values will then undergo validations
			stringstream input(inCmd);
			string command;
			vector<string> commands;

			while (getline(input, command, ' '))
			{
				command.erase(0, command.find_first_not_of(' '));
				command.erase(command.find_last_not_of(' ') + 1);
				commands.push_back(command);
			}

			//Maximum of 2 input paramaters only: COMMAND POSITION
			if (commands.size() > 2)
			{
				throw InputException("Invalid input format!");
			}

			string inputCommand;
			string inputParams;

			for (size_t i = 0; i < commands.size(); ++i)
			{
				if (i == 0)
				{
					inputCommand = commands[0];
				}
				else if (i == 1)
				{
					inputParams = commands[1];
				}
			}

			//Make sure that command passed is valid
			RobotActions actions;
			exception excMessage;
			RobotActions::Commands cmdEnum;

			if (actions.validateCommand(inputCommand, excMessage, cmdEnum) != SUCCESS)
			{
				throw ActionException(excMessage.what());
			}
			else
			{
				int position[1][3];

				//Make sure that position is provided in PLACE command and it is valid INTEGER [0-5], INTEGER[0-5], DIRECTION[NORTH, EAST, SOUTH, WEST]
				if (cmdEnum == RobotActions::Commands::PLACE)
				{
					if (trim(inputParams).empty())
					{
						throw InputException("Empty position!");
					}
					else
					{
						if (actions.validatePosition(inputParams, position, excMessage) != SUCCESS)
						{
							throw ActionException(excMessage.what());
						}
					}
				}
				//No position is expected for other commands
				else
				{
					if (!trim(inputParams).empty())
					{
						throw InputException("Invalid input format!");
					}
				}

				//Now call the appropriate functions for each command
				switch (cmdEnum)
				{
				case RobotActions::Commands::PLACE:
					if (actions.place(position, excMessage) != SUCCESS)
					{
						throw ActionException(excMessage.what());
					}
					break;
				case RobotActions::Commands::MOVE:
					if (actions.move(excMessage) != SUCCESS)
					{
						throw ActionException(excMessage.what());
					}
					break;
				case RobotActions::Commands::LEFT:
					if (actions.left(excMessage) != SUCCESS)
					{
						throw ActionException(excMessage.what());
					}
					break;
				case RobotActions::Commands::RIGHT:
					if (actions.right(excMessage) != SUCCESS)
					{
						throw ActionException(excMessage.what());
					}
					break;
				case RobotActions::Commands::REPORT:
					if (actions.report(excMessage) != SUCCESS)
					{
						throw ActionException(excMessage.what());
					}
					break;
				default:
					throw ActionException("Invalid command!");
					break;
				}

				setSuccessfulRun(true);
				setExceptionMessage("");
			}
		}
	}
	catch (const ActionException& e)
	{
		setSuccessfulRun(false);
		setExceptionMessage(e.what());
	}
	catch (const InputException& e)
	{
		setSuccessfulRun(false);
		setExceptionMessage(e.what());
	}
	catch (...)
	{
		setSuccessfulRun(false);
		setExceptionMessage("Unhandled exception!");
	}
}

void ToyRobotMain::runApplication()
{
	while (true)
	{
		string userInput;
		getline(cin, userInput);

		processInputCommand(userInput);
	}
}