Toy Robot in C++

The Toy Robot Simulation is a console application that simulates the movement of a toy robot on a square tabletop with dimensions of 5 units x 5 units. The robot is allowed to roam freely on the table's surface but must be prevented from falling off the edge. The application processes commands to control the robot's placement and movement.

## Features

- Simulates a toy robot on a 5x5 unit table.
- Accepts commands to control the robot's position and orientation.
- Prevents the robot from falling off the table during movement.
- Commands are processed in sequence, with a focus on validating initial placement.

## Commands

The application accepts the following commands:

- **PLACE X,Y,F**: 
  - Places the toy robot on the table at position `(X, Y)` and facing one of the four cardinal directions: `NORTH`, `SOUTH`, `EAST`, or `WEST`.
  - The first command must be a `PLACE` command.
  - Subsequent commands can include additional `PLACE` commands.

- **MOVE**: 
  - Moves the toy robot one unit forward in the direction it is currently facing.
  - Moves that would cause the robot to fall off the table are ignored.

- **LEFT**: 
  - Rotates the robot 90 degrees to the left without changing its position.

- **RIGHT**: 
  - Rotates the robot 90 degrees to the right without changing its position.

- **REPORT**: 
  - Outputs the robot's current position and facing direction.

## Table of Contents
- [Recompile](recompile)
- [Run the Application](#run-the-application)
- [Test the Application](#test-the-application)
- [Automated Testing](#test-the-application)

## Recompile
1. Clone the repository:
   * Open MS Visual Studio and Create an empty project
   * In the toolbar, select Git > Clone a repository
   * In the 'Repository Location', put the location:
       https://github.com/ojersa/ToyRobot.git
   * Change 'Path' based on your preference
   * Press Clone

2. Compile
   * In the toolbar, select Build > Clean Solution
   * In the toolbar, select Build > Build Solution

3. Set-up the startup project
   * In the 'Solutions Explorer', right click on 'ToyRobot'.
   * Select Properties.
   * In Common Properties > Project Dependencies, from the dropdown options for 'Single Startup Project', select ToyRobotApp.
   * Press Ok

## Run the application
1. Locate the .exe file. The path should be (Path)\x64\Debug\ToyRobotApp.exe
2. Double click on the ToyRobotApp.exe file.

## Test the application
   * [Run the executable file](#run-the-application)
   * Find the test data here: (Path)\ToyRobotApp\TestData.txt

## Automated Testing
   * Open MS Visual Studio open the project
   * In the toolbar, select Test > Test Explorer
   * Press Ctrl + R,V



   

