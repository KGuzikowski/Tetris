#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "graphic.h"

block_shape generate_block();
// side = 0 means left and side = 1 means right
void move_to_sides(block_shape *block, int side,  int vel);

void move_down(block_shape *block, int vel);

#endif // LOGIC_H_INCLUDED
