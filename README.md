## Toy Robot in C++

The Toy Robot Simulation is a console application that simulates the movement of a toy robot on a square tabletop with dimensions of 5 units x 5 units. The robot is allowed to roam freely on the table's surface but must be prevented from falling off the edge. The application processes commands to control the robot's placement and movement.

## Features

- Simulates a toy robot on a 5x5 unit table.
- Accepts commands to control the robot's position and orientation.
- Prevents the robot from falling off the table during movement.

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

- **EXAMPLE INPUT AND OUTPUT**: 
  - Example Input and Output:
  - a)----------------
  - PLACE 0,0,NORTH
  - MOVE
  - REPORT
  - Output: 0,1,NORTH
  -
  - b)----------------
  - PLACE 0,0,NORTH
  - LEFT
  - REPORT
  - Output: 0,0,WEST
  -
  - c)----------------
  - PLACE 1,2,EAST
  - MOVE
  - MOVE
  - LEFT
  - MOVE
  - REPORT
  - Output: 3,3,NORTH

## Developer Notes
- [Recompile](recompile)
- [Run the Application](#run-the-application)
- [Runnable Unit Testing](#runnable-unit-testing)
- [Test the Application](#test-the-application)

## Recompile
1. Clone the repository:
   * Open MS Visual Studio and Create an empty project
   * In the toolbar, select Git > Clone a repository
   * In the 'Repository Location', put the location:
       https://github.com/ojersa/ToyRobot.git
   * Change 'Path' based on your preference
   * Select 'Clone'

2. Compile
   * In the toolbar, select Build > Clean Solution
   * In the toolbar, select Build > Build Solution

3. Set-up the startup project
   * In the 'Solutions Explorer', right click on 'ToyRobot'.
   * Select Properties.
   * In Common Properties > Project Dependencies,select ToyRobotApp in the dropdown options for 'Single Startup Project'.
   * Select 'Ok'

## Run the application
1. Locate the .exe file. The path should be (Path)\x64\Debug\ToyRobotApp.exe
2. Double click on the ToyRobotApp.exe file.
3. Click on 'X' icon to close the application.

## Runnable Unit Testing
   * Open MS Visual Studio open the project
   * In the toolbar, select Test > Test Explorer
   * Press Ctrl + R,V

## Test the application
   * [Run the executable file](#run-the-application)
   * Here are some sample test scenarios you can use to validate the application:

     ### Test Scenario Group 1: PLACE first
- The following scenarios show that other commands will be ignored if PLACE is not yet called

    **Input Commands:**
    ```cmd
    MOVE
    ```

    **Expected Output:**
    ```cmd
    ```

    **Input Commands:**
    ```cmd
    LEFT
    ```

    **Expected Output:**
    ```cmd
    ```

    **Input Commands:**
    ```cmd
    RIGHT
    ```

    **Expected Output:**
    ```cmd
    ```
    **Input Commands:**
    ```cmd
    REPORT
    ```

    **Expected Output:**
    ```cmd
    ```

    **Input Commands:**
    ```cmd
    PLACE 1,2,NORTH
    REPORT
    ```

    **Expected Output:**
    ```cmd
    Output: 1,2,NORTH
    ```

### Test Scenario Group 2: Incorrect input
- The following scenarios show that commands will be ignored if input is invalid


    Input Commands (empty input)
    ```cmd
           
    ```

    **Expected Output:**
    ```cmd
    ```


    **Input Commands (invalid command):**
    ```cmd
    PLACE 2,2,EAST
    TEST 1,0,SOUTH
    REPORT
    ```

    **Expected Output:**
    ```cmd
    Output: 2,2,EAST
    ```

    **Input Commands (more than 2 input strings):**
    ```cmd
    PLACE 1,1,SOUTH
    PLACE 1,0,SOUTH LEFT
    REPORT
    ```

    **Expected Output:**
    ```cmd
    Output: 1,1,SOUTH
    ```

    **Input Commands (invalid x position):**
    ```cmd
    PLACE 1,3,NORTH
    PLACE x,2,NORTH
    REPORT
    ```

    **Expected Output:**
    ```cmd
    Output: 1,3,NORTH
    ```

    **Input Commands (invalid y position):**
    ```cmd
    PLACE 3,2,WEST
    PLACE 3,y,NORTH
    REPORT
    ```

    **Expected Output:**
    ```cmd
    Output: 3,2,WEST
    ```

    **Input Commands (invalid direction):**
    ```cmd
    PLACE 3,2,NORTH
    PLACE 1,2,f
    REPORT
    ```

    **Expected Output:**
    ```cmd
    Output: 3,2,NORTH
    ```

### Test Scenario Group 3:
- positive and negative tests for PLACE command

    **Input Commands:**
    ```cmd
    PLACE 1,0,NORTH
    REPORT
    ```

    **Expected Output:**
    ```cmd
    Output: 1,0,NORTH
    ```
    
    **Input Commands (x position is out of bounds):**
    ```cmd
    PLACE 0,3,NORTH
    PLACE 7,1,NORTH
    REPORT
    ```

    **Expected Output:**
    ```cmd
    Output: 0,3,NORTH
    ```
    
    **Input Commands (x position is out of bounds):**
    ```cmd
    PLACE 2,2,SOUTH
    PLACE 5,-2,NORTH
    REPORT
    ```

    **Expected Output:**
    ```cmd
    Output: 2,2,SOUTH
    ```

### Test Scenario Group 4:
- positive and negative tests for MOVE command

    **Input Commands:**
    ```cmd
    PLACE 4,3,EAST
    MOVE
    REPORT
    ```
    
    **Expected Output:**
    ```cmd
    Output: 5,3,EAST
    ```
    
    **Input Commands (out of bounds):**
    ```cmd
    PLACE 0,1,WEST
    MOVE
    REPORT
    ```
    
    **Expected Output:**
    ```cmd
    Output: 0,1,WEST
    ```
    
    **Input Commands (with position):**
    ```cmd
    PLACE 2,1,WEST 
    MOVE 1,1,WEST
    REPORT
    ```
    
    **Expected Output:**
    ```cmd
    Output: 2,1,WEST 
    ```

### Test Scenario Group 5:
- positive and negative tests for LEFT command

    **Input Commands:**
    ```cmd
    PLACE 3,3,EAST
    LEFT
    REPORT
    ```
    
    **Expected Output:**
    ```cmd
    Output: 3,3,NORTH
    ```
    
    **Input Commands (with position):**
    ```cmd
    PLACE 2,1,SOUTH 
    LEFT 2,1,EAST
    REPORT
    ```
    
    **Expected Output:**
    ```cmd
    Output: 2,1,SOUTH  
    ```

### Test Scenario Group 6:
- positive and negative tests for RIGHT command

    **Input Commands:**
    ```cmd
    PLACE 3,3,EAST
    RIGHT
    REPORT
    ```
    
    **Expected Output:**
    ```cmd
    Output: 3,3,SOUTH
    ```
    
    **Input Commands (with position):**
    ```cmd
    PLACE 2,1,SOUTH 
    RIGHT 2,1,WEST
    REPORT
    ```
    
    **Expected Output:**
    ```cmd
    Output: 2,1,SOUTH  
    ```


### Test Scenario Group 7:
- positive and negative tests for REPORT command

    **Input Commands:**
    ```cmd
    PLACE 3,3,SOUTH
    REPORT
    ```
    
    **Expected Output:**
    ```cmd
    Output: 3,3,SOUTH
    ```
    
    **Input Commands (with position):**
    ```cmd
    PLACE 2,1,SOUTH
    REPORT 2,1,SOUTH
    ```
    
    **Expected Output:**
    ```cmd
    ```



   

