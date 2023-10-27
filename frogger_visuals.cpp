#include "splashkit.h"
#include "frogger_visuals.h"

#define WINDOW_WIDTH    600
#define WINDOW_HEIGHT   400

// Global variable to store the window.
window frogger_window; 

void initialise_graphics() {
    frogger_window = open_window("Frogger", WINDOW_WIDTH, WINDOW_HEIGHT);
}

void close_graphics() {
    close_window(frogger_window);
}

void update_graphics(char first_layer_letters[SIZE][SIZE], char second_layer_letters[SIZE][SIZE]) {
    clear_window(frogger_window, COLOR_BLUE);  // First, clear the previous frame

    int cell_width = WINDOW_WIDTH / SIZE;
    int cell_height = WINDOW_HEIGHT / SIZE;

    // Iterate over first layer and draw
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            char current_tile = first_layer_letters[row][col];
            if (current_tile == 'o') {
                int lilypad_x = col * cell_width + cell_width / 2; // Center position
                int lilypad_y = row * cell_height + cell_height / 2; // Center position
                fill_circle(COLOR_LIME, lilypad_x, lilypad_y, cell_height/2);
            } else if (current_tile == 'x') {
                fill_rectangle(COLOR_YELLOW, col * cell_width, row * cell_height, cell_width, cell_height);
            } else if (current_tile == '~') {
                // already blue
            } else if (current_tile == 'T') {
                int turtle_x = col * cell_width + cell_width / 2; // Center position
                int turtle_y = row * cell_height + cell_height / 2; // Center position
                fill_circle(COLOR_RED, turtle_x, turtle_y, cell_height/2);
            } else if (current_tile == 'L') {
                fill_rectangle(COLOR_CHOCOLATE, col * cell_width, row * cell_height, cell_width, cell_height);
            }
        }
    }

    // Iterate over second layer and draw
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            char current_tile = second_layer_letters[row][col];
            int entity_x = col * cell_width + cell_width / 2; // Center position
            int entity_y = row * cell_height + cell_height / 2; // Center position
            
            if (current_tile == 'F') {
                fill_circle(COLOR_GREEN, entity_x, entity_y, cell_height/4); // Half the size of lilypad
            } else if (current_tile == 'S') {
                fill_circle(COLOR_BLACK, entity_x, entity_y, 0.75 * cell_height/2); // 75% size of lilypad
            } else if (current_tile == 'B') {
                fill_circle(COLOR_DARK_GRAY, entity_x, entity_y, cell_height/4); // Same size as frogger
            }  
        }
    }

    // add the grid
    for (int i = 0; i < SIZE; i++) {
        int line_start_x = i * cell_width;
        draw_line(COLOR_BLACK, line_start_x, 0, line_start_x, WINDOW_HEIGHT);
    }
    for (int i = 0; i < SIZE; i++) {
        int line_start_y = i * cell_height;
        draw_line(COLOR_BLACK, 0, line_start_y, WINDOW_WIDTH, line_start_y);
    }


    
    refresh_screen();  // Refresh the window to display updated graphics.
}
