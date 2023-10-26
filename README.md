# Frogger

**Objective:** Navigate the frog safely across the river and avoid introduced obstacles to win.

## Gameplay

1. Start the game by executing the frogger binary.
2. Enter the desired commands as prompted.
3. Navigate the board, make strategic decisions, and aim to achieve the game's objective.
4. Be cautious of obstacles and challenges introduced during the gameplay.
5. Enjoy the game!

> **Note:** To use a custom game setup, run `cat custom_set_up.txt - | ./frogger`.

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

To gracefully terminate the game at any point, simply press `Control + D`. This will signal an end-of-file (EOF) to the game, prompting it to exit safely.
