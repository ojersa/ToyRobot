#include "pch.h"
#include "CppUnitTest.h"
#include "../ToyRobotLib/RobotActions.h"
#include "../ToyRobotLib/ToyRobotMain.h"
#include "../ToyRobotApp/ToyRobotApp.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool successRun = true;
bool failureRun = false;
string noError = "";

namespace UnitTestRobot
{
	TEST_CLASS(TestPlaceCommand)
	{
	public:

		TEST_METHOD(validPlace)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "PLACE";
			string position = "1,1,NORTH";
			string input = mainCommand + " " + position;

			//validate using report that position is same as the input
			string reportCommand = "REPORT";
			string reportOutput = "Output: " + position + "\n";

			ToyRobotMain robot;
			robot.processInputCommand(input);

			//Runs should be success and no exception message
			Assert::AreEqual(successRun, robot.getSuccessfulRun());
			Assert::AreEqual(noError, robot.getExceptionMessage());

			//Get the position from the standard output and compare to expected
			ostringstream outputBuffer;
			streambuf* originalCout = cout.rdbuf(outputBuffer.rdbuf());

			robot.processInputCommand(reportCommand);

			cout.rdbuf(originalCout);

			Assert::AreEqual(reportOutput, outputBuffer.str());
		}

		TEST_METHOD(xOutOfBounds)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "PLACE";
			string position = "7,1,NORTH";
			string input = mainCommand + " " + position;

			//Exception should be thrown with this message
			string excMessage = "Position over the limit!";

			ToyRobotMain robot;
			robot.processInputCommand(input);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());
		}

		TEST_METHOD(yOutOfBounds)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "PLACE";
			string position = "5,-2,NORTH";
			string input = mainCommand + " " + position;

			//Exception should be thrown with this message
			string excMessage = "Position over the limit!";

			ToyRobotMain robot;
			robot.processInputCommand(input);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());
		}
	};

	TEST_CLASS(TestMoveCommand)
	{
	public:

		TEST_METHOD(validMove)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "MOVE";
			string placeCommand = "PLACE";
			string position = "4,3,EAST";
			string input = placeCommand + " " + position;

			//validate using report that position is +1 in direction
			string reportCommand = "REPORT";
			string newPosition = "5,3,EAST";
			string reportOutput = "Output: " + newPosition + "\n";

			ToyRobotMain robot;
			robot.processInputCommand(input);
			robot.processInputCommand(mainCommand);

			//Runs should be success and no exception message
			Assert::AreEqual(successRun, robot.getSuccessfulRun());
			Assert::AreEqual(noError, robot.getExceptionMessage());

			//Get the position from the standard output and compare to expected
			ostringstream outputBuffer;
			streambuf* originalCout = cout.rdbuf(outputBuffer.rdbuf());

			robot.processInputCommand(reportCommand);

			cout.rdbuf(originalCout);

			Assert::AreEqual(reportOutput, outputBuffer.str());

		}

		TEST_METHOD(moveBeforePlace)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "MOVE";

			//Exception should be thrown with this message
			string excMessage = "Cannot MOVE before PLACE!";

			ToyRobotMain robot;
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());
		}

		TEST_METHOD(moveOutOfBounds)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "MOVE";
			string placeCommand = "PLACE";
			string position = "0,1,WEST";
			string input = placeCommand + " " + position;

			//validate using report that position did not change
			string reportCommand = "REPORT";
			string reportOutput = "Output: " + position + "\n";

			//Exception should be thrown with this message
			string excMessage = "Cannot MOVE here!";

			ToyRobotMain robot;
			robot.processInputCommand(input);
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());

			//Get the position from the standard output and compare to expected
			ostringstream outputBuffer;
			streambuf* originalCout = cout.rdbuf(outputBuffer.rdbuf());

			robot.processInputCommand(reportCommand);

			cout.rdbuf(originalCout);

			Assert::AreEqual(reportOutput, outputBuffer.str());
		}

		TEST_METHOD(moveWithPosition)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "MOVE 1,1,NORTH";
			string placeCommand = "PLACE";
			string position = "0,1,WEST";
			string input = placeCommand + " " + position;

			//validate using report that position did not change
			string reportCommand = "REPORT";
			string reportOutput = "Output: " + position + "\n";

			//Exception should be thrown with this message
			string excMessage = "Invalid input format!";

			ToyRobotMain robot;
			robot.processInputCommand(input);
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());

			//Get the position from the standard output and compare to expected
			ostringstream outputBuffer;
			streambuf* originalCout = cout.rdbuf(outputBuffer.rdbuf());

			robot.processInputCommand(reportCommand);

			cout.rdbuf(originalCout);

			Assert::AreEqual(reportOutput, outputBuffer.str());
		}
	};

	TEST_CLASS(TestLeftCommand)
	{
	public:

		TEST_METHOD(validLeft)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "LEFT";
			string placeCommand = "PLACE";
			string position = "3,3,EAST";
			string input = placeCommand + " " + position;

			//validate using report that direction changed to the left
			string reportCommand = "REPORT";
			string newPosition = "3,3,NORTH";
			string reportOutput = "Output: " + newPosition + "\n";

			ToyRobotMain robot;
			robot.processInputCommand(input);
			robot.processInputCommand(mainCommand);

			//Runs should be success and no exception message
			Assert::AreEqual(successRun, robot.getSuccessfulRun());
			Assert::AreEqual(noError, robot.getExceptionMessage());

			//Get the position from the standard output and compare to expected
			ostringstream outputBuffer;
			streambuf* originalCout = cout.rdbuf(outputBuffer.rdbuf());

			robot.processInputCommand(reportCommand);

			cout.rdbuf(originalCout);

			Assert::AreEqual(reportOutput, outputBuffer.str());

		}

		TEST_METHOD(leftBeforePlace)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "LEFT";

			//Exception should be thrown with this message
			string excMessage = "Cannot ROTATE LEFT before PLACE!";

			ToyRobotMain robot;
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());
		}

		TEST_METHOD(leftWithPosition)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "LEFT 1,1,NORTH";
			string placeCommand = "PLACE";
			string position = "2,1,SOUTH";
			string input = placeCommand + " " + position;

			//validate using report that direction did not change
			string reportCommand = "REPORT";
			string reportOutput = "Output: " + position + "\n";

			//Exception should be thrown with this message
			string excMessage = "Invalid input format!";

			ToyRobotMain robot;
			robot.processInputCommand(input);
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());

			//Get the position from the standard output and compare to expected
			ostringstream outputBuffer;
			streambuf* originalCout = cout.rdbuf(outputBuffer.rdbuf());

			robot.processInputCommand(reportCommand);

			cout.rdbuf(originalCout);

			Assert::AreEqual(reportOutput, outputBuffer.str());
		}
	};

	TEST_CLASS(TestRightCommand)
	{
	public:

		TEST_METHOD(validRight)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "RIGHT";
			string placeCommand = "PLACE";
			string position = "3,3,WEST";
			string input = placeCommand + " " + position;

			//validate using report that direction changed to the right
			string reportCommand = "REPORT";
			string newPosition = "3,3,NORTH";
			string reportOutput = "Output: " + newPosition + "\n";

			ToyRobotMain robot;
			robot.processInputCommand(input);
			robot.processInputCommand(mainCommand);

			//Runs should be success and no exception message
			Assert::AreEqual(successRun, robot.getSuccessfulRun());
			Assert::AreEqual(noError, robot.getExceptionMessage());

			//Get the position from the standard output and compare to expected
			ostringstream outputBuffer;
			streambuf* originalCout = cout.rdbuf(outputBuffer.rdbuf());

			robot.processInputCommand(reportCommand);

			cout.rdbuf(originalCout);

			Assert::AreEqual(reportOutput, outputBuffer.str());

		}

		TEST_METHOD(rightBeforePlace)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "RIGHT";

			//Exception should be thrown with this message
			string excMessage = "Cannot ROTATE RIGHT before PLACE!";

			ToyRobotMain robot;
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());
		}

		TEST_METHOD(rightWithPosition)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "RIGHT 1,1,NORTH";
			string placeCommand = "PLACE";
			string position = "2,1,SOUTH";
			string input = placeCommand + " " + position;

			//validate using report that direction did not change
			string reportCommand = "REPORT";
			string reportOutput = "Output: " + position + "\n";

			//Exception should be thrown with this message
			string excMessage = "Invalid input format!";

			ToyRobotMain robot;
			robot.processInputCommand(input);
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());

			//Get the position from the standard output and compare to expected
			ostringstream outputBuffer;
			streambuf* originalCout = cout.rdbuf(outputBuffer.rdbuf());

			robot.processInputCommand(reportCommand);

			cout.rdbuf(originalCout);

			Assert::AreEqual(reportOutput, outputBuffer.str());
		}
	};

	TEST_CLASS(TestReportCommand)
	{
	public:

		TEST_METHOD(validReport)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "REPORT";
			string placeCommand = "PLACE";
			string position = "3,3,SOUTH";
			string input = placeCommand + " " + position;

			//Output should be +1 in the position is same with the input
			string reportCommand = "REPORT";
			string newPosition = "3,3,SOUTH";
			string reportOutput = "Output: " + newPosition + "\n";

			ToyRobotMain robot;
			robot.processInputCommand(input);

			//Get the position from the standard output and compare to expected
			ostringstream outputBuffer;
			streambuf* originalCout = cout.rdbuf(outputBuffer.rdbuf());

			robot.processInputCommand(reportCommand);

			//Runs should be success and no exception message
			Assert::AreEqual(successRun, robot.getSuccessfulRun());
			Assert::AreEqual(noError, robot.getExceptionMessage());

			cout.rdbuf(originalCout);

			Assert::AreEqual(reportOutput, outputBuffer.str());

		}

		TEST_METHOD(reportBeforePlace)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "REPORT";

			//Exception should be thrown with this message
			string excMessage = "Cannot REPORT before PLACE!";

			ToyRobotMain robot;
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());
		}

		TEST_METHOD(reportWithPosition)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "REPORT 1,1,NORTH";
			string placeCommand = "PLACE";
			string position = "2,1,SOUTH";
			string input = placeCommand + " " + position;

			//validate using report that position did not change
			string reportCommand = "REPORT";
			string reportOutput = "Output: " + position + "\n";

			//Exception should be thrown with this message
			string excMessage = "Invalid input format!";

			ToyRobotMain robot;
			robot.processInputCommand(input);
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());

			//Get the position from the standard output and compare to expected
			ostringstream outputBuffer;
			streambuf* originalCout = cout.rdbuf(outputBuffer.rdbuf());

			robot.processInputCommand(reportCommand);

			cout.rdbuf(originalCout);

			Assert::AreEqual(reportOutput, outputBuffer.str());
		}
	};

	TEST_CLASS(TestInputString)
	{
	public:

		TEST_METHOD(emptyInput)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "     ";

			//Exception should be thrown with this message
			string excMessage = "Empty user input!";

			ToyRobotMain robot;
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());
		}

		TEST_METHOD(invalidCommand)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "TEST 1,0,SOUTH";

			//Exception should be thrown with this message
			string excMessage = "Invalid command!";

			ToyRobotMain robot;
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());
		}

		TEST_METHOD(moreThan2Inputs)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "PLACE 1,2,NORTH LEFT";

			//Exception should be thrown with this message
			string excMessage = "Invalid input format!";

			ToyRobotMain robot;
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());
		}

		TEST_METHOD(invalidXPosition)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "PLACE x,1,NORTH";

			//Exception should be thrown with this message
			string excMessage = "Invalid x position!";

			ToyRobotMain robot;
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());
		}

		TEST_METHOD(invalidYPosition)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "PLACE 1,y,NORTH";

			//Exception should be thrown with this message
			string excMessage = "Invalid y position!";

			ToyRobotMain robot;
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());
		}

		TEST_METHOD(invalidDirection)
		{
			//Clear flag, robot is not placed
			RobotActions actions;
			actions.setIsRobotPlaced(false);

			//test data
			string mainCommand = "PLACE 1,2,f";

			//Exception should be thrown with this message
			string excMessage = "Invalid Direction!";

			ToyRobotMain robot;
			robot.processInputCommand(mainCommand);

			//Runs should be failure and with exception message
			Assert::AreEqual(failureRun, robot.getSuccessfulRun());
			Assert::AreEqual(excMessage, robot.getExceptionMessage());
		}
	};

}