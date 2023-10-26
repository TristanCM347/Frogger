// The Game Frogger
// This is a simplified version of frogger where you have to get frogger across
// the river to win.

#include <stdio.h>
#include <math.h>

#define SIZE        9

#define TRUE        1
#define FALSE       0

#define UNKNOWN    -1

#define WON         1
#define LOST       -1
#define PLAYING     0

#define RIGHT       0
#define LEFT        1
#define UP          2
#define DOWN        3
#define NOTHING     4

#define NEITHER    -1

#define ON          1
#define OFF         0


enum tile_type {LILLYPAD, BANK, WATER, TURTLE, LOG};

struct bug_properties {
    int movement_direction;
    // LEFT or RIGHT.
    int bug_on_tile;
    // TRUE or FALSE.
    int bug_has_moved;
    // TRUE or FALSE.
    int superbug;
    //TRUE or FALSE.
};

struct board_tile {
    enum tile_type type;
    // The type of piece it is (water, bank, etc.)
    int occupied;
    // TRUE or FALSE based on if Frogger is there.
    struct bug_properties bug;
    // TRUE or FALSE based on if bug is there.
};

struct distances {
    int best_move;
    double distance_of_best_move;
    double distance_of_nothing;
    double distance_of_up;
    double distance_of_left;
    double distance_of_right;
    double distance_of_down;
};

void print_board(struct board_tile game_board[SIZE][SIZE]);
char print_board_2nd_function(struct board_tile game_board[SIZE][SIZE], 
char type_char, int col, int row);
void log_on_game_board_function(struct board_tile game_board[SIZE][SIZE],
int game_mode);
void log_on_game_board_function_2(struct board_tile game_board[SIZE][SIZE],
int log_row, int start_column, int end_column);
void clear_row_function(struct board_tile game_board[SIZE][SIZE], 
int game_mode);
void remove_log_function(
    struct board_tile game_board[SIZE][SIZE],
    int game_mode
);
void remove_log_function_2(struct board_tile game_board[SIZE][SIZE], 
int remove_col, int remove_row);
void removing_log(struct board_tile game_board[SIZE][SIZE], 
int remove_col, int remove_row, int valid_remove);
void move_up(struct board_tile game_board[SIZE][SIZE]);
void move_down(struct board_tile game_board[SIZE][SIZE]);
void move_left(struct board_tile game_board[SIZE][SIZE]);
void move_right(struct board_tile game_board[SIZE][SIZE]);
int finding_froggers_row(struct board_tile game_board[SIZE][SIZE]);
int finding_froggers_col(struct board_tile game_board[SIZE][SIZE]);
void move_consequences(struct board_tile game_board[SIZE][SIZE], 
int **amount_of_lives_ptr2, int **game_state_ptr2);
int win_or_lose(int game_state, int sentinal);
void adding_bug(struct board_tile game_board[SIZE][SIZE], int game_mode);
void adding_superbug(struct board_tile game_board[SIZE][SIZE], int game_mode);
void checking_for_bugs(struct board_tile game_board[SIZE][SIZE]);
int checking_the_first_direction(struct board_tile game_board[SIZE][SIZE], 
int row, int col, int bug_cant_go_original_way);
int checking_the_second_direction(struct board_tile game_board[SIZE][SIZE], 
int row, int col, int bug_cant_go_original_way);
void moving_the_bugs(struct board_tile game_board[SIZE][SIZE], 
int row, int col);
void moving_superbugs(struct board_tile game_board[SIZE][SIZE], 
int row, int col);
void moving_normal_bugs(struct board_tile game_board[SIZE][SIZE], 
int row, int col);
struct distances finding_best_move(struct board_tile game_board[SIZE][SIZE], 
int row, int col, struct distances distance, int up_valid, int left_valid, 
int right_valid, int down_valid);
void actually_moving_superbug(struct board_tile game_board[SIZE][SIZE], 
int row, int col, struct distances distance);
void placing_superbug_up(struct board_tile game_board[SIZE][SIZE], 
int row, int col);
void placing_superbug_left(struct board_tile game_board[SIZE][SIZE], 
int row, int col);
void placing_superbug_right(struct board_tile game_board[SIZE][SIZE], 
int row, int col);
void placing_superbug_down(struct board_tile game_board[SIZE][SIZE], 
int row, int col);
void moving_rows(struct board_tile game_board[SIZE][SIZE]);
void copying_gameboard_to_temp(struct board_tile game_board[SIZE][SIZE], 
struct board_tile game_board_temp[SIZE][SIZE]);
void rows_going_right(struct board_tile game_board[SIZE][SIZE], 
struct board_tile game_board_temp[SIZE][SIZE]);
void rows_going_left(struct board_tile game_board[SIZE][SIZE], 
struct board_tile game_board_temp[SIZE][SIZE]);
void initialise_gameboard(struct board_tile game_board[SIZE][SIZE]);
void adding_turtles_and_start_game(struct board_tile game_board[SIZE][SIZE]);
int changing_game_mode_function(struct board_tile game_board[SIZE][SIZE], 
int game_mode);
void invalid_inputs(struct board_tile game_board[SIZE][SIZE], int game_mode);
void movement_sequence(struct board_tile game_board[SIZE][SIZE], 
int *amount_of_lives_ptr1, int *game_state_ptr1, int game_mode);
void command_loop(struct board_tile game_board[SIZE][SIZE]);
double maths_formula(struct board_tile game_board[SIZE][SIZE], 
int row, int col);


//main
int main(void) {
    printf("Welcome to Frogger!\n");
    struct board_tile game_board[SIZE][SIZE];
    
    initialise_gameboard(game_board);
    
    adding_turtles_and_start_game(game_board);
    
    command_loop(game_board);
    
    printf("Thank you for playing Frogger!\n");
    return 0;
}


// takes in commands from terminal and acts accordingly
void command_loop(struct board_tile game_board[SIZE][SIZE]) {
    int game_state = PLAYING;
    int amount_of_lives = 3; 
    int sentinal = TRUE;
    int game_mode = OFF;
    
    while (sentinal) {
        printf("Enter command: ");
        char scanned_char;
        int scanf_return = scanf(" %c", &scanned_char);
        
        if (scanf_return != 1) {
            sentinal = FALSE;
        } else if (scanned_char == 'l') {
            log_on_game_board_function(game_board, game_mode);
        } else if (scanned_char == 'c') {
            clear_row_function(game_board, game_mode);
        } else if (scanned_char == 'r') {
            remove_log_function(game_board, game_mode);           
        } else if (scanned_char == 'w') {
            move_up(game_board);
            movement_sequence(game_board, &amount_of_lives, &game_state,
            game_mode);
        } else if (scanned_char == 's') {
            move_down(game_board);
            movement_sequence(game_board, &amount_of_lives, &game_state,
            game_mode);
        } else if (scanned_char == 'a') {
            move_left(game_board);            
            movement_sequence(game_board, &amount_of_lives, &game_state,
            game_mode);
        } else if (scanned_char == 'd') {
            move_right(game_board);            
            movement_sequence(game_board, &amount_of_lives, &game_state,
            game_mode);
        } else if (scanned_char == 'b') {
            adding_bug(game_board, game_mode);   
        } else if (scanned_char == 'g') {
            game_mode = changing_game_mode_function(game_board, game_mode);      
        } else if (scanned_char == 'z') {
            adding_superbug(game_board, game_mode);
        } else {
            invalid_inputs(game_board, game_mode);
        }

        sentinal = win_or_lose(game_state, sentinal);
    }
}


// does everyhting after player moves, like changing the gameboard
void movement_sequence(struct board_tile game_board[SIZE][SIZE], 
int *amount_of_lives_ptr1, int *game_state_ptr1, int game_mode) {
    checking_for_bugs(game_board);
    
    if (game_mode == ON) {
        moving_rows(game_board);
    }
    
    print_board(game_board);
    
    move_consequences(game_board, &amount_of_lives_ptr1, &game_state_ptr1);

}


// checks invalid inputs from terminal
void invalid_inputs(struct board_tile game_board[SIZE][SIZE], int game_mode) {
    if (game_mode == ON) {
        printf("This command is not supported in game mode.\n");
    }
    
    print_board(game_board);
}


// changes gamemode or not if g is inputed as a command by returning gamemode
// variable
int changing_game_mode_function(struct board_tile game_board[SIZE][SIZE], 
int game_mode) {
    int on_or_off;
    scanf("%d", &on_or_off);
    if (game_mode == ON) {
        if (on_or_off == OFF) {
            game_mode = OFF;
            printf("\n### GAME MODE EXITED ###\n\n");
        }
    } else if (game_mode == OFF) {
        if (on_or_off == ON) {
            game_mode = ON;
            printf("\n### GAME MODE ACTIVATED ###\n\n");
        }
    }
    
    print_board(game_board);
    
    return game_mode;
}


// detects if the game has been won or lost and acts accordingly by returning 
// sentinal
int win_or_lose(int game_state, int sentinal) {
    //if statement for scenario when game is lost
    if (game_state == LOST) {
        printf("\n");
        printf(" !! GAME OVER !! \n\n");
        
        sentinal = FALSE;
    }

    //if statement for scenario when game is won
    if (game_state == WON) {
        printf("\n");
        printf("Wahoo!! You Won!\n\n");
        
        sentinal = FALSE;
    }

    return sentinal;
}


// adds turtles to gameboard at the start of the game and then starts the game
void adding_turtles_and_start_game(struct board_tile game_board[SIZE][SIZE]) {
    printf("How many turtles? ");
    int number_of_turtles;
    scanf("%d", &number_of_turtles);
    
    if (number_of_turtles > 0) {
        printf("Enter pairs:\n");
    }
    
    int turtle_row;
    int turtle_col;
    for (int i = 0; i < number_of_turtles; i++) {
        scanf("%d %d", &turtle_row, &turtle_col);
        
        if (0 < turtle_row && turtle_row < (SIZE - 1)) {
            game_board[turtle_row][turtle_col].type = TURTLE;
        }
    }

    printf("Game Started\n");
    
    print_board(game_board);
}


// initialises gameboard at the very start of the game
void initialise_gameboard(struct board_tile game_board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        
        for (int col = 0; col < SIZE; col++) {
            game_board[row][col].type = WATER;
            game_board[row][col].occupied = FALSE;
            game_board[row][col].bug.bug_on_tile = FALSE;
            game_board[row][col].bug.movement_direction = RIGHT;
            game_board[row][col].bug.bug_has_moved = FALSE;
            game_board[row][col].bug.superbug = FALSE;
        }
    }
    
    game_board[(SIZE - 1) ][4].occupied = TRUE;
    
    for (int col = 0; col < SIZE; col++) {
        game_board[(SIZE - 1) ][col].type = BANK; 
    }
    
    int col = 0;
    while (col < SIZE) {
        game_board[0][col].type = LILLYPAD;
        col = col + 2;
    }
}


// function for when l is inputed in terminal that starts trying to put logs on
// the gameboard by scanning coordinates then acting accordingly
void log_on_game_board_function(struct board_tile game_board[SIZE][SIZE],
int game_mode) {
    int log_row;
    int start_column;
    int end_column;
    scanf("%d %d %d", &log_row, &start_column, &end_column);

    if (game_mode == ON) {
        printf("This command is not supported in game mode.\n");
    } else if (game_mode == OFF) {
        log_on_game_board_function_2(game_board, log_row, start_column,
        end_column);
    }

    print_board(game_board);
}


// checks coordinates of log inputed then places log if its a valid log
void log_on_game_board_function_2(struct board_tile game_board[SIZE][SIZE],
int log_row, int start_column, int end_column) {

    //checking for turtles on row with if statement and loop
    int is_there_turtle_in_row = FALSE;
    for (int i = 0; i < SIZE; i++) {
        if (game_board[log_row][i].type == TURTLE) {
            is_there_turtle_in_row = TRUE;
        }
    }
    
    //checking if its out of bounds with if statement
    int log_on_wrong_row = FALSE;
    if (log_row == 0 || log_row == (SIZE - 1)) {
        log_on_wrong_row = TRUE;
    }

    //checking or changing if log is off the screen with if statements
    int log_on_board = TRUE;
    if (start_column < 0 && end_column >= 0) {
        start_column = 0;
    } else if (end_column < 0) {
        log_on_board = FALSE;
    }

    if (end_column > (SIZE - 1) && start_column <= (SIZE - 1)) {
        end_column = (SIZE - 1);
    } else if (start_column > (SIZE - 1)) {
        log_on_board = FALSE;
    }

    //placing log by changing the gameboard array with a loop if log is valid
    if (log_on_board == TRUE && log_on_wrong_row == FALSE 
    && is_there_turtle_in_row == FALSE) {
        int i = start_column;
        while (i <= end_column) {
            game_board[log_row][i].type = LOG;
            i++;
        }
    }
}


// clears row on gameboardif c is inputed, 
// and every other consideration is checked
void clear_row_function(struct board_tile game_board[SIZE][SIZE], 
int game_mode) {
    int row_to_clear;
    scanf("%d", &row_to_clear);
    
    if (game_mode == ON) {
        printf("This command is not supported in game mode.\n");
    } else if (game_mode == OFF) {
        //checking if its out of bounds with if statement
        int valid_row_to_clear = TRUE;
        if (row_to_clear < 1 || row_to_clear > 7) {
            valid_row_to_clear = FALSE;
        }

        //checking if froggers on the row with if statement
        int froggers_row = finding_froggers_row(game_board);
    
        if (froggers_row == row_to_clear) {
            valid_row_to_clear = FALSE;
        }
    
        //clearing row with loops if its a valid row to clear
        if (valid_row_to_clear == TRUE) {
            for (int col = 0; col < SIZE; col++) {
                game_board[row_to_clear][col].type = WATER;
                game_board[row_to_clear][col].bug.bug_on_tile = FALSE;
                game_board[row_to_clear][col].bug.superbug = FALSE;
            }
        }
    }
    
    print_board(game_board);
    
}


// starts trying to remove an individual log on the gameboard if r is inputed
// by scanning values and seeing if gamemode is on
void remove_log_function(struct board_tile game_board[SIZE][SIZE], 
int game_mode) {
    int remove_col;
    int remove_row;
    scanf("%d %d", &remove_row, &remove_col);
    
    if (game_mode == ON) {
        printf("This command is not supported in game mode.\n");
    } else if (game_mode == OFF) {
        remove_log_function_2(game_board, remove_col, remove_row);
    }
    
    print_board(game_board);
}


// checks to see if coordinates given are valid to remove log
void remove_log_function_2(struct board_tile game_board[SIZE][SIZE], 
int remove_col, int remove_row) {

    //checking if its out of bounds with if statements
    int valid_remove = TRUE;
    if (remove_col < 0 || remove_col > (SIZE - 1)) {
        valid_remove = FALSE;
    }
    if (remove_row > 7 || remove_row < 1) {
        valid_remove = FALSE;
    }
    
    //checking if coordinate is water with if statements
    if (valid_remove == TRUE && 
    game_board[remove_row][remove_col].type == WATER) {
        valid_remove = FALSE;
    }

    //checking if turtle is on the row meaning there cant be any logs with loop
    // and if statements
    if (valid_remove == TRUE) {
        for (int i = 0; i < SIZE; i++) {
            if (game_board[remove_row][i].type == TURTLE) {
                valid_remove = FALSE;
            }
        }
    }

    //checking for frogger on the log with loops and if statements
    int i = remove_col;
    while (valid_remove == TRUE && i >= 0 && i <= (SIZE - 1) && 
    game_board[remove_row][i].type != WATER 
    ) {
        if (game_board[remove_row][i].occupied == TRUE) {
            valid_remove = FALSE;
        }
        i++;
    }
    i = remove_col - 1;
    while (valid_remove == TRUE && i >= 0 && i <= (SIZE - 1) && 
    game_board[remove_row][i].type != WATER) {
        if (game_board[remove_row][i].occupied == TRUE) {
            valid_remove = FALSE;
        }
        i--;
    }

    removing_log(game_board, remove_col, remove_row, valid_remove);
}


// checks if move is valid and if so removes log on gameboard
void removing_log(struct board_tile game_board[SIZE][SIZE], 
int remove_col, int remove_row, int valid_remove) {
    //removing the log
    if (valid_remove == TRUE) {
        int i = remove_col;
        
        while (i >= 0 && i <= (SIZE - 1) 
        && game_board[remove_row][i].type != WATER) {
            game_board[remove_row][i].type = WATER;
            game_board[remove_row][i].bug.bug_on_tile = FALSE;
            game_board[remove_row][i].bug.superbug = FALSE;
            i++;
        }
        i = remove_col - 1;
        
        while (i >= 0 && i <= (SIZE - 1) 
        && game_board[remove_row][i].type != WATER) {
            game_board[remove_row][i].type = WATER;
            game_board[remove_row][i].bug.bug_on_tile = FALSE;
            game_board[remove_row][i].bug.superbug = FALSE;
            i--;
        }
    } 
}


// moves frogger up on the gameboard
void move_up(struct board_tile game_board[SIZE][SIZE]) {
    //find froggers row
    int froggers_row = finding_froggers_row(game_board);
    int valid_move = TRUE;
    
    if (froggers_row == 0) {
        valid_move = FALSE;
    }
    
    int froggers_col = finding_froggers_col(game_board);

    //move frogger with reassignmnet
    if (valid_move == TRUE) {
        game_board[froggers_row][froggers_col].occupied = FALSE;
        game_board[froggers_row - 1][froggers_col].occupied = TRUE;
    }

}


// moves frogger down on the gameboard
void move_down(struct board_tile game_board[SIZE][SIZE]) {
    //find froggers row
    int froggers_row = finding_froggers_row(game_board);
    int valid_move = TRUE;
    
    if (froggers_row == (SIZE - 1)) {
        valid_move = FALSE;
    }
    
    int froggers_col = finding_froggers_col(game_board);

    //move frogger with reassignment
    if (valid_move == TRUE) {
        game_board[froggers_row][froggers_col].occupied = FALSE;
        game_board[froggers_row + 1][froggers_col].occupied = TRUE;
    }
}


// moves frogger right on the gameboard
void move_right(struct board_tile game_board[SIZE][SIZE]) {
    //find froggers col
    int froggers_col = finding_froggers_col(game_board);
    int valid_move = TRUE;
    
    if (froggers_col == (SIZE - 1)) {
        valid_move = FALSE;
    }
    
    int froggers_row = finding_froggers_row(game_board);

    //move frogger with reassignment
    if (valid_move == TRUE) {
        game_board[froggers_row][froggers_col].occupied = FALSE;
        game_board[froggers_row][froggers_col + 1].occupied = TRUE;
    }

}


// moves frogger left on the gameboard
void move_left(struct board_tile game_board[SIZE][SIZE]) {
    //find froggers col
    int froggers_col = finding_froggers_col(game_board);
    int valid_move = TRUE;
    
    if (froggers_col == 0) {
        valid_move = FALSE;
    }
    
    int froggers_row = finding_froggers_row(game_board);

    //move frogger with reassignment
    if (valid_move == TRUE) {
        game_board[froggers_row][froggers_col].occupied = FALSE;
        game_board[froggers_row][froggers_col - 1].occupied = TRUE;
    }

}


// finds froggers row with a loop and returns value
int finding_froggers_row(struct board_tile game_board[SIZE][SIZE]) {
    int froggers_row = UNKNOWN;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (game_board[row][col].occupied == TRUE) {
                froggers_row = row;
            }
        }
    }
    
    return froggers_row;
}


// finds froggers column with a loop and returns value
int finding_froggers_col(struct board_tile game_board[SIZE][SIZE]) {
    int froggers_col = UNKNOWN;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (game_board[row][col].occupied == TRUE) {
                froggers_col = col;
            }
        }
    }
    
    return froggers_col;
}


// this function checks what happens to frogger after all the gamebaord is
// changed and then returns pointer values to desribe what happens
// e.g. whether he dies or lives 
void move_consequences(struct board_tile game_board[SIZE][SIZE], 
int **amount_of_lives_ptr2, int **game_state_ptr2) {
    
    int frogger_dies = FALSE;
    //checking for if game is won with if statement
    if (game_board[0][0].occupied == TRUE || game_board[0][2].occupied == TRUE 
    || game_board[0][4].occupied == TRUE || game_board[0][6].occupied == TRUE
    || game_board[0][0].occupied == TRUE) {
        **game_state_ptr2 = WON;
    }

    int froggers_col = finding_froggers_col(game_board);
    int froggers_row = finding_froggers_row(game_board);

    //checking for if move kills frogger if if statement
    if (game_board[froggers_row][froggers_col].type == WATER ||
    game_board[froggers_row][froggers_col].bug.bug_on_tile == TRUE) {
        frogger_dies = TRUE;
    }

    //changes amount of lives and/or game state 
    // if frogger dies with reassingnemnt
    if (frogger_dies == TRUE) {
        game_board[froggers_row][froggers_col].occupied = FALSE;
        game_board[ (SIZE - 1) ][4].occupied = TRUE;
        **amount_of_lives_ptr2 = **amount_of_lives_ptr2 - 1;
    }
    
    if (**amount_of_lives_ptr2 != 0 && frogger_dies == TRUE) {
        printf("\n");
        printf("# LIVES LEFT: %d # \n\n", **amount_of_lives_ptr2);
        print_board(game_board);
    } else if (**amount_of_lives_ptr2 == 0) {
        **game_state_ptr2 = LOST;
    }
        
}


// if coordinates are valid adds a normal bug to the gameboard
void adding_bug(struct board_tile game_board[SIZE][SIZE], int game_mode) {
    int bugs_row;
    int bugs_col;
    scanf("%d %d", &bugs_row, &bugs_col);
    if (game_mode == ON) {
        printf("This command is not supported in game mode.\n");
    } else if (game_mode == OFF) {
        int valid_move = TRUE;
        
        //checking if bug is out of bounds wiht if statments
        if (bugs_row <= 0 || bugs_row >= (SIZE - 1)) {
            valid_move = FALSE;
        }
        if (bugs_col < 0 || bugs_col >= SIZE) {
            valid_move = FALSE;
        }

        //checking if bug is placed on frogger wiht if statement
        if (valid_move == TRUE && 
        game_board[bugs_row][bugs_col].occupied == TRUE) {
            valid_move = FALSE;
        }

        //checking if bug is placed on water with if statement
        if (valid_move == TRUE && 
        game_board[bugs_row][bugs_col].type == WATER) {
            valid_move = FALSE;
        }

        //checking if bug is placed on another bug with if statement
        if (valid_move == TRUE 
        && game_board[bugs_row][bugs_col].bug.bug_on_tile == TRUE) {
            valid_move = FALSE;
        }

        //placing bug with reassignment if coordintaes are valid
        if (valid_move == TRUE) {
            game_board[bugs_row][bugs_col].bug.bug_on_tile = TRUE;
        }
    }
    
    print_board(game_board);
}


// if coordintates are valid adds superbug to gameboard
void adding_superbug(struct board_tile game_board[SIZE][SIZE], int game_mode) {
    int superbugs_row;
    int superbugs_col;
    scanf("%d %d", &superbugs_row, &superbugs_col);
    
    if (game_mode == ON) {
        printf("This command is not supported in game mode.\n");
    } else if (game_mode == OFF) {
        int valid_move = TRUE;
        
        //checking if superbug is out of bounds with if statement
        if (superbugs_row <= 0 || superbugs_row >= (SIZE - 1)) {
            valid_move = FALSE;
        }
        if (superbugs_col < 0 || superbugs_col >= SIZE) {
            valid_move = FALSE;
        }
        
        //checking if superbug is placed on frogger with if statement
        if (valid_move == TRUE && 
        game_board[superbugs_row][superbugs_col].occupied == TRUE) {
            valid_move = FALSE;
        }

        //checking if superbug is placed on water with if statement
        if (valid_move == TRUE && 
        game_board[superbugs_row][superbugs_col].type == WATER) {
            valid_move = FALSE;
        }

        //checking if superbug is placed on another bug with if statement
        if (valid_move == TRUE 
        && game_board[superbugs_row][superbugs_col].bug.bug_on_tile == TRUE) {
            valid_move = FALSE;
        }

        //placing superbug with reassignment if coordinates are valid
        if (valid_move == TRUE) {
            game_board[superbugs_row][superbugs_col].bug.bug_on_tile = TRUE;
            game_board[superbugs_row][superbugs_col].bug.superbug = TRUE;
        }
    }
    
    print_board(game_board);
}


// with a loop goes through all board tiles and checks for bugs 
// then acts accordingly 
// afterwards resetting bug has moved variables
void checking_for_bugs(struct board_tile game_board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            
            //checks if theres a bug on the tile and it has not moved
            // with an if statement
            if (game_board[row][col].bug.bug_on_tile == TRUE 
            && game_board[row][col].bug.bug_has_moved == FALSE) {
                moving_the_bugs(game_board, row, col);
            }
        }
    }
    
    //resetting bug has moved variables all to FALSE,
    // since all the bugs have just moved with a loop
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            game_board[row][col].bug.bug_has_moved = FALSE;    
        }
    }

}  


// checks if the bug on the tile is a superbug or normal bug
void moving_the_bugs(struct board_tile game_board[SIZE][SIZE], 
int row, int col) {
    if (game_board[row][col].bug.superbug == TRUE) {
        moving_superbugs(game_board, row, col);
    } else if (game_board[row][col].bug.superbug == FALSE) {
        moving_normal_bugs(game_board, row, col);
    }
}


//chekcing if bug can go a its current direction, 
// if not changing its movement direction and
// outputs direction bug needs to move
int checking_the_first_direction(struct board_tile game_board[SIZE][SIZE], 
int row, int col, int bug_cant_go_original_way) {
    
    if (game_board[row][col].bug.movement_direction == RIGHT) {
        
        if (col == (SIZE - 1) || game_board[row][col + 1].type == WATER 
        || game_board[row][col + 1].bug.bug_on_tile == TRUE) {
            
            bug_cant_go_original_way = TRUE;
            game_board[row][col].bug.movement_direction = LEFT; 
        }

    } else if (game_board[row][col].bug.movement_direction == LEFT) {
        
        if (col == 0 || game_board[row][col - 1].type == WATER 
        || game_board[row][col - 1].bug.bug_on_tile == TRUE) {
            
            bug_cant_go_original_way = TRUE;
            game_board[row][col].bug.movement_direction = RIGHT;
        }
    }
    
    return bug_cant_go_original_way;
}


//if couldn't move on first move, checking if bug can move in other 
//direction, if not (its stranded) resetting movement direction
// outpuds direction bug needs to move
int checking_the_second_direction(struct board_tile game_board[SIZE][SIZE], 
int row, int col, int bug_cant_go_original_way) {
    
    if (game_board[row][col].bug.movement_direction == RIGHT) {
            
        if (col == (SIZE - 1) || game_board[row][col + 1].type == WATER 
        || game_board[row][col + 1].bug.bug_on_tile == TRUE) {
                
            bug_cant_go_original_way = NEITHER;
            game_board[row][col].bug.movement_direction = LEFT;
        }

    } else if (game_board[row][col].bug.movement_direction == LEFT) {
            
        if (col == 0 || game_board[row][col - 1].type == WATER 
        || game_board[row][col - 1].bug.bug_on_tile == TRUE) {
                
            bug_cant_go_original_way = NEITHER;
            game_board[row][col].bug.movement_direction = RIGHT;
        }
    }
    
    return bug_cant_go_original_way;
}


// checking valid movements of the normal bugs and then moving accordingly
void moving_normal_bugs(struct board_tile game_board[SIZE][SIZE], 
int row, int col) {
    int bug_cant_go_original_way = FALSE;

    bug_cant_go_original_way = checking_the_first_direction(game_board, 
    row, col, bug_cant_go_original_way);
    
    if (bug_cant_go_original_way == TRUE) {
        bug_cant_go_original_way = 
        checking_the_second_direction(game_board, row, col, 
        bug_cant_go_original_way);
    }
    
    //moving the bug if its not stranded using resassignment of variables
    if (bug_cant_go_original_way != NEITHER) {
        if (game_board[row][col].bug.movement_direction == LEFT) {
            
            game_board[row][col - 1].bug.bug_on_tile = TRUE; 
            game_board[row][col - 1].bug.movement_direction = LEFT; 
            game_board[row][col - 1].bug.bug_has_moved = TRUE;
            
            //initialise the previous tiles bug variables with 
            // reassignment of varibales
            game_board[row][col].bug.bug_on_tile = FALSE;
            game_board[row][col].bug.movement_direction = RIGHT;
            game_board[row][col].bug.bug_has_moved = FALSE;

        } else if (game_board[row][col].bug.movement_direction == RIGHT) {
            
            game_board[row][col + 1].bug.bug_on_tile = TRUE; 
            game_board[row][col + 1].bug.movement_direction = RIGHT; 
            game_board[row][col + 1].bug.bug_has_moved = TRUE;
            
            //initialise the previous tiles bug variables with reassignment
            // of variables
            game_board[row][col].bug.bug_on_tile = FALSE;
            game_board[row][col].bug.movement_direction = RIGHT;
            game_board[row][col].bug.bug_has_moved = FALSE;
        }
    }
}


// proceedure to move superbug 
void moving_superbugs(struct board_tile game_board[SIZE][SIZE], 
int row, int col) {
    int up_valid = TRUE;
    int left_valid = TRUE;
    int right_valid = TRUE;
    int down_valid = TRUE;
    
    //check all valid squares that are adjacent with if statement
    if (row == 1 || game_board[row - 1][col].type == WATER 
    || game_board[row - 1][col].bug.bug_on_tile == TRUE) {
        up_valid = FALSE;
    }
    if (col == 0 || game_board[row][col - 1].type == WATER 
    || game_board[row][col - 1].bug.bug_on_tile == TRUE) {
        left_valid = FALSE;
    }
    if (col == (SIZE - 1) || game_board[row][col + 1].type == WATER 
    || game_board[row][col + 1].bug.bug_on_tile == TRUE) {
        right_valid = FALSE;
    }
    if (row == 7 || game_board[row + 1][col].type == WATER 
    || game_board[row + 1][col].bug.bug_on_tile == TRUE) {
        down_valid = FALSE;
    }

    // finds the best move for superbug based on the now found valid move
    // it can make with these functiosn below 
    struct distances distance;
    
    distance.distance_of_nothing = maths_formula(game_board, row, col);

    distance.best_move = NOTHING;
    distance.distance_of_best_move = distance.distance_of_nothing;

    distance = finding_best_move(game_board, row, col, distance, 
    up_valid, left_valid, right_valid, down_valid);

    actually_moving_superbug(game_board, row, col, distance);
}


// finds the best move for superbug based on if that move produces a 
// shorter distance to frogger if it makes it
// this function then returns these findings in the struct distances distance
struct distances finding_best_move(struct board_tile game_board[SIZE][SIZE], 
int row, int col, struct distances distance, int up_valid, int left_valid, 
int right_valid, int down_valid) {
    if (up_valid == TRUE) {
        row = row - 1;
        distance.distance_of_up = maths_formula(game_board, row, col);
        row = row + 1;
        if (distance.distance_of_up < distance.distance_of_best_move) {
            distance.best_move = UP;
            distance.distance_of_best_move = distance.distance_of_up;
        }
    }

    if (left_valid == TRUE) {
        col = col - 1;
        distance.distance_of_left = maths_formula(game_board, row, col);
        col = col + 1;

        if (distance.distance_of_left < distance.distance_of_best_move) {
            distance.best_move = LEFT;
            distance.distance_of_best_move = distance.distance_of_left;
        }
    }

    if (right_valid == TRUE) {
        col = col + 1;
        distance.distance_of_right = maths_formula(game_board, row, col);
        col = col - 1;

        if (distance.distance_of_right < distance.distance_of_best_move) {
            distance.best_move = RIGHT;
            distance.distance_of_best_move = distance.distance_of_right;
        }
    }

    if (down_valid == TRUE) {
        row = row + 1;
        distance.distance_of_down = maths_formula(game_board, row, col);
        row = row - 1;

        if (distance.distance_of_down < distance.distance_of_best_move) {
            distance.best_move = DOWN;
            distance.distance_of_best_move = distance.distance_of_down;
        }
    }

    return distance;
}


// depending on the best move for superbug gives the correspodning 
// movement function to run
void actually_moving_superbug(struct board_tile game_board[SIZE][SIZE], 
int row, int col, struct distances distance) {
    if (distance.best_move == NOTHING) {
        //do nothing
    } else if (distance.best_move == UP) {
        placing_superbug_up(game_board, row, col);
    } else if (distance.best_move == LEFT) {
        placing_superbug_left(game_board, row, col);
    } else if (distance.best_move == RIGHT) {
        placing_superbug_right(game_board, row, col);
    } else if (distance.best_move == DOWN) {
        placing_superbug_down(game_board, row, col);
    }
}


// changes gamemboard to move superbug up
void placing_superbug_up(struct board_tile game_board[SIZE][SIZE], 
int row, int col) {
    //move the superbugs variables up via reassignment of varibales
    game_board[row - 1][col].bug.bug_on_tile = TRUE; 
    game_board[row - 1][col].bug.superbug = TRUE; 
    game_board[row - 1][col].bug.bug_has_moved = TRUE;
            
    //initialise the previous tiles superbug variables
    game_board[row][col].bug.bug_on_tile = FALSE;
    game_board[row][col].bug.superbug = FALSE;
    game_board[row][col].bug.bug_has_moved = FALSE;
}


// changes gamemboard to move superbug left
void placing_superbug_left(struct board_tile game_board[SIZE][SIZE], 
int row, int col) {
    //move the superbugs variables left via reassignment of varibales
    game_board[row][col - 1].bug.bug_on_tile = TRUE; 
    game_board[row][col - 1].bug.superbug = TRUE; 
    game_board[row][col - 1].bug.bug_has_moved = TRUE;
            
    //initialise the previous tiles superbug variables
    game_board[row][col].bug.bug_on_tile = FALSE;
    game_board[row][col].bug.superbug = FALSE;
    game_board[row][col].bug.bug_has_moved = FALSE;
}


// changes gamemboard to move superbug right
void placing_superbug_right(struct board_tile game_board[SIZE][SIZE], 
int row, int col) {
    //move the superbugs variables right via reassignment of varibales
    game_board[row][col + 1].bug.bug_on_tile = TRUE; 
    game_board[row][col + 1].bug.superbug = TRUE; 
    game_board[row][col + 1].bug.bug_has_moved = TRUE;
            
    //initialise the previous tiles superbug variables
    game_board[row][col].bug.bug_on_tile = FALSE;
    game_board[row][col].bug.superbug = FALSE;
    game_board[row][col].bug.bug_has_moved = FALSE;
}


// changes gamemboard to move superbug down
void placing_superbug_down(struct board_tile game_board[SIZE][SIZE], 
int row, int col) {
    //move the superbugs variables down via reassignment of varibales
    game_board[row + 1][col].bug.bug_on_tile = TRUE; 
    game_board[row + 1][col].bug.superbug = TRUE; 
    game_board[row + 1][col].bug.bug_has_moved = TRUE;
            
    //initialise the previous tiles superbug variables
    game_board[row][col].bug.bug_on_tile = FALSE;
    game_board[row][col].bug.superbug = FALSE;
    game_board[row][col].bug.bug_has_moved = FALSE;
}


// runs the distance formula with inputed values 
//and returns the value its equal to
double maths_formula(struct board_tile game_board[SIZE][SIZE], 
int row, int col) {
    double froggers_col = finding_froggers_col(game_board);
    double froggers_row = finding_froggers_row(game_board);
    double distance;
    
    distance = sqrt(((froggers_col - col) * (froggers_col - col))
    + ((froggers_row - row) * (froggers_row - row)));
    
    return distance;
}


// copies gameboard to a temp value
void copying_gameboard_to_temp(struct board_tile game_board[SIZE][SIZE], 
struct board_tile game_board_temp[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {  
        for (int col = 0; col < SIZE; col++) {
            game_board_temp[row][col].type = 
            game_board[row][col].type;
            game_board_temp[row][col].occupied = 
            game_board[row][col].occupied;
            game_board_temp[row][col].bug.bug_on_tile = 
            game_board[row][col].bug.bug_on_tile;
            game_board_temp[row][col].bug.movement_direction = 
            game_board[row][col].bug.movement_direction;
            game_board_temp[row][col].bug.bug_has_moved = 
            game_board[row][col].bug.bug_has_moved;
            game_board_temp[row][col].bug.superbug = 
            game_board[row][col].bug.superbug;
        }
    }
}


// moves required rows left
void rows_going_left(struct board_tile game_board[SIZE][SIZE], 
struct board_tile game_board_temp[SIZE][SIZE]) {
    for (int row = 1; row < (SIZE - 1); row += 2) {
        for (int col = 1; col < SIZE; col++) {
            //this does all the non wrapping tiles with a loop
            game_board[row][col - 1].type = game_board_temp[row][col].type;
            game_board[row][col - 1].occupied = 
            game_board_temp[row][col].occupied;
            game_board[row][col - 1].bug.bug_on_tile =
            game_board_temp[row][col].bug.bug_on_tile;
            game_board[row][col - 1].bug.movement_direction =
            game_board_temp[row][col].bug.movement_direction;
            game_board[row][col - 1].bug.bug_has_moved =
            game_board_temp[row][col].bug.bug_has_moved;
            game_board[row][col - 1].bug.superbug =
            game_board_temp[row][col].bug.superbug;
        }

        //this does the wrapping tiles with reassignment of variables
        game_board[row][SIZE - 1].type = game_board_temp[row][0].type;
        game_board[row][SIZE - 1].bug.bug_on_tile =
        game_board_temp[row][0].bug.bug_on_tile;
        game_board[row][SIZE - 1].bug.movement_direction =
        game_board_temp[row][0].bug.movement_direction;
        game_board[row][SIZE - 1].bug.bug_has_moved =
        game_board_temp[row][0].bug.bug_has_moved;
        game_board[row][SIZE - 1].bug.superbug =
        game_board_temp[row][0].bug.superbug;
        game_board[row][SIZE - 1].occupied = FALSE;

        //this pushes frogger off if condition met
        if (game_board_temp[row][0].occupied == TRUE) {
            game_board[row][0].occupied = TRUE;
        }
    }
}


// moves required rows right
void rows_going_right(struct board_tile game_board[SIZE][SIZE], 
struct board_tile game_board_temp[SIZE][SIZE]) {
    for (int row = 2; row < (SIZE - 1); row += 2) {
        for (int col = 0; col < (SIZE - 1); col++) {
            //this does all the non wrapping tiles with a loop
            game_board[row][col + 1].type = game_board_temp[row][col].type;
            game_board[row][col + 1].occupied = 
            game_board_temp[row][col].occupied;
            game_board[row][col + 1].bug.bug_on_tile =
            game_board_temp[row][col].bug.bug_on_tile;
            game_board[row][col + 1].bug.movement_direction =
            game_board_temp[row][col].bug.movement_direction;
            game_board[row][col + 1].bug.bug_has_moved =
            game_board_temp[row][col].bug.bug_has_moved;
            game_board[row][col + 1].bug.superbug =
            game_board_temp[row][col].bug.superbug;
        }

        //this does the wrapping tiles with reassignemtn of variables
        game_board[row][0].type = game_board_temp[row][SIZE - 1].type;
        game_board[row][0].bug.bug_on_tile =
        game_board_temp[row][SIZE - 1].bug.bug_on_tile;
        game_board[row][0].bug.movement_direction =
        game_board_temp[row][SIZE - 1].bug.movement_direction;
        game_board[row][0].bug.bug_has_moved =
        game_board_temp[row][SIZE - 1].bug.bug_has_moved;
        game_board[row][0].bug.superbug =
        game_board_temp[row][SIZE - 1].bug.superbug;
        game_board[row][0].occupied = FALSE;

        //this pushes frogger off if conditon met
        if (game_board_temp[row][SIZE - 1].occupied == TRUE) {
            game_board[row][SIZE - 1].occupied = TRUE;
        }
    }
}


// goes through the steps required to move the rows on the gameboard
void moving_rows(struct board_tile game_board[SIZE][SIZE]) {
    struct board_tile game_board_temp[SIZE][SIZE];
    
    copying_gameboard_to_temp(game_board, game_board_temp);
    
    rows_going_left(game_board, game_board_temp);
    
    rows_going_right(game_board, game_board_temp);
}


// prints the gameboard
void print_board(struct board_tile game_board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            char type_char = '\0';
            if (game_board[row][col].occupied) {
                type_char = 'F';
            } else if (game_board[row][col].bug.superbug == TRUE) {
                type_char = 'S';
            } else if (game_board[row][col].bug.bug_on_tile == TRUE) {
                type_char = 'B';
            } else {
                type_char = print_board_2nd_function(game_board, type_char, 
                col, row);
            }
            printf("%c ", type_char);
        }
        printf("\n");
    }
}

// checks within the tile type enum to see what char to print and returns that
// char since theres no bugs or frogger on tile
char print_board_2nd_function(struct board_tile game_board[SIZE][SIZE], 
char type_char, int col, int row) {
    enum tile_type type = game_board[row][col].type;
    if (type == LILLYPAD) {
        type_char = 'o';
    } else if (type == BANK) {
        type_char = 'x';
    } else if (type == WATER) {
        type_char = '~';
    } else if (type == TURTLE) {
        type_char = 'T';
    } else if (type == LOG) {
        type_char = 'L';
    }
    return type_char;
}
