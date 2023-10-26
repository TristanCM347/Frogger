#include "splashkit.h"

#define NUM_COLS 9
#define NUM_ROWS 9

// This is some starter code for the challenve exercise. 
// Please use the folliwing documentation to learn more about 
// what functions are available to you:
// SplashKit graphics docs: https://splashkit.io/api/graphics/
// SplashKit user input docs: https://splashkit.io/api/input/

// To compile your splashkit program: skm clang++ program.c -o program

// Some useful functions are:
// fill rectangle: https://splashkit.io/api/graphics/#fill-rectangle-record
// key typed:  https://splashkit.io/api/input/#key-typed

// This is a function you may consider writing (amongst others!) :) 
// void draw_text_in_cell(int cell_x, int cell_y, string text)
// 
// This function draws a grid and is an example of how to call functions
// using SplashKit
void draw_grid(window w, int num_cols, int num_rows)
{
    int window_width = current_window_width();
    int window_height = current_window_height();

    int column_width = window_width / num_cols;
    int column_height = window_height / num_cols;

    for (int i = 0; i < num_cols; i++)
    {
        int line_start_x = i * column_width;
        draw_line(COLOR_BLACK, line_start_x, 0, line_start_x, window_height);
    }
    for (int i = 0; i < num_rows; i++)
    {
        int line_start_y = i * column_height;
        draw_line(COLOR_BLACK, 0, line_start_y, window_width, line_start_y);
    }
}

// Main starts here... 
int main()
{
    // The graphics will be drawn in a separate window
    // This opens a window with title Frogger of size 600x400
    window w = open_window("Frogger", 600, 400);

    // Whilst the window remains opened
    while (!window_close_requested(w))
    {
        // checks for any user interaction (button clicks)
        // You will need this to be able to read when user closes
        // the window by clicking
        process_events();

        // This is an example of calling a draw_rectangle function
        // https://splashkit.io/api/graphics/#draw-rectangle-record
        // draw_rectangle(COLOR_GREEN, 20, 20, 20, 20);
        
        // Calling the sample function we wrote ourselves:
        draw_grid(w, NUM_COLS, NUM_ROWS);

        // paints pixels to the graphics window
        refresh_screen();
    }
    return 0;
}