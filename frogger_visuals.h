#ifndef FROGGER_VISUALS_H
#define FROGGER_VISUALS_H

#define SIZE        9

#ifdef __cplusplus
extern "C" {
#endif

void close_graphics();
void initialise_graphics();
void update_graphics(char first_layer_letters[SIZE][SIZE], char second_layer_letters[SIZE][SIZE]);

#ifdef __cplusplus
}
#endif

#endif // FROGGER_VISUALS_H
