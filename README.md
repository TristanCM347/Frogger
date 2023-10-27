# Frogger.c

**Objective:** Navigate the frog safely across the river and avoid introduced obstacles to win.

## Gameplay

1. Start the game by executing the frogger binary.
2. Enter the desired commands as prompted.
3. Navigate the board, make strategic decisions, and aim to achieve the game's objective.
4. Be cautious of obstacles and challenges introduced during the gameplay.
5. Enjoy the game!

> **Note:** To use a example game setup, run `cat example_set_up.txt - | ./frogger`.

## Game Mechanics Description

### Game Board
|    | R0 | R1 | R2 | R3 | R4 | R5 | R6 | R7 | R8 |
|----|----|----|----|----|----|----|----|----|----|
| C0 |    |    |    |    |    |    |    |    |    |
| C1 |    |    |    |    |    |    |    |    |    |
| C2 |    |    |    |    |    |    |    |    |    |
| C3 |    |    |    |    |    |    |    |    |    |
| C4 |    |    |    |    |    |    |    |    |    |
| C5 |    |    |    |    |    |    |    |    |    |
| C6 |    |    |    |    |    |    |    |    |    |
| C7 |    |    |    |    |    |    |    |    |    |
| C8 |    |    |    |    |    |    |    |    |    |

### Moving Rows
These are unique elements in the game that don't actively chase or pursue the player. Instead, they act as passive transport mechanisms. The player has to actively move onto these rows. Once on them, the player is automatically transported in a predefined direction by the moving row.

### Superbug
The **Superbug** is a more intelligent and challenging adversary in the game. Unlike regular bugs, the Superbug possesses advanced pathfinding abilities. It calculates the shortest path to the player and relentlessly pursues them. This requires the player to strategize and think quickly to avoid being caught by the Superbug.

### Bugs
Regular bugs in the game have a simpler movement pattern. They move left and right, offering predictable yet challenging obstacles for the player. Their consistent movement pattern makes them different from the Superbug, but they still pose a threat to the player if not navigated correctly.


## Commands

### Movement

- **w**: Move the frog upwards.
- **s**: Move the frog downwards.
- **a**: Move the frog to the left.
- **d**: Move the frog to the right.
- **q**: Frogger stays still.

### Game Elements

- **l [row] [start_col] [end_col]**: Place a log on the game board at the specified row, starting from start_col and ending at end_col.
- **c [row]**: Clear obstacles in the specified row.
- **r [row] [col]**: Remove a log from the game board at the specified row and column.
- **b [row] [col]**: Add a bug at the specified row and column.
- **z [row] [col]**: Introduce a superbug at the specified row and column.

### Game Modes (Moving Rows)

- **g [0/1]**: Toggle game modes. Use g 1 to activate moving rows and g 0 to deactivate them.

### Game Termination

To gracefully terminate the game at any point, simply press `Control + D`. This will signal an end-of-file (EOF) to the game, prompting it to exit safely. Unexpected behaviour will arise otherwise.

## Compilation Instructions

For the whole version of this game to function correctly, you must first install **SplashKit**. Otherwise comment out function calls to frogger_visuals.cpp

### Installing SplashKit
To get SplashKit, follow the installation guide provided [here](https://splashkit.io/articles/installation/).

### Alternate Configuration without SplashKit
If you choose not to install SplashKit or face any issues during its installation, you can still run a non-graphical version of the game. To do this, comment out any function calls related to `frogger_visuals.cpp` in the source code.

### Compiling the Game
Once SplashKit is set up, you can compile the game using the following commands:

```bash
skm g++ -c frogger.c
skm g++ -c frogger_visuals.cpp
skm g++ frogger.o frogger_visuals.o -o frogger
