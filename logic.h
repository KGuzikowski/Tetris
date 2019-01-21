#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "graphic.h"

block_shape generate_block();
// side = 0 means left and side = 1 means right
void move_to_sides(block_shape *block, int side,  int vel, grid_elem grid[15][10]);

void can_move_down(block_shape *block, grid_elem grid[15][10], int vel, int *score);
int can_move_right(block_shape *block, grid_elem grid[15][10], int steps);
int can_move_left(block_shape *block, grid_elem grid[15][10], int steps);

void rotate(block_shape *block, grid_elem grid[15][10]);

int gameOver(block_shape *block, grid_elem grid[15][10]);

void destroyLine(grid_elem grid[15][10], int *score);

#endif // LOGIC_H_INCLUDED
