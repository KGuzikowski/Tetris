#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "logic.h"
#include "graphic.h"

#define WIDTH 500
#define HEIGHT 900

//generating random block
block_shape generate_block(){
    int block_num;
    block_num = (rand()%7) + 1;
    //block_num = 1;

    if(block_num == 1){
        block_shape block;
        block.kind_of_block = 1;
        block.isDone = 0;
        SDL_Color color = {234, 184, 46, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 250;
        block.x = (rand()%9 + 1)*50;
        block.rotated = 0;
        block.steps_moved = 0;
        return block;
    } else if(block_num == 2){
        block_shape block;
        block.kind_of_block = 2;
        block.isDone = 0;
        SDL_Color color = {48, 223, 56, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 200;
        block.x = (rand()%9)*50;
        block.rotated = 0;
        block.steps_moved = 0;
        return block;
    } else if(block_num == 3){
        block_shape block;
        block.kind_of_block = 3;
        block.isDone = 0;
        SDL_Color color = {202, 65, 28, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 200;
        block.x = (rand()%9+1)*50;
        block.rotated = 0;
        block.steps_moved = 0;
        return block;
    } else if(block_num == 4){
        block_shape block;
        block.kind_of_block = 4;
        block.isDone = 0;
        SDL_Color color = {28, 202, 199, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 200;
        block.x = (rand()%8 + 1)*50;
        block.rotated = 0;
        block.steps_moved = 0;
        return block;
    } else if(block_num == 5){
        block_shape block;
        block.kind_of_block = 5;
        block.isDone = 0;
        SDL_Color color = {238, 27, 185, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 200;
        block.x = (rand()%8+1)*50;
        block.rotated = 0;
        block.steps_moved = 0;
        return block;
    } else if(block_num == 6){
        block_shape block;
        block.kind_of_block = 6;
        block.isDone = 0;
        SDL_Color color = {41, 34, 236, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 200;
        block.x = (rand()%8 + 1)*50;
        block.rotated = 0;
        block.steps_moved = 0;
        return block;
    } else if(block_num == 7){
        block_shape block;
        block.kind_of_block = 7;
        block.isDone = 0;
        SDL_Color color = {242, 162, 105, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 250;
        block.x = (rand()%9+1)*50;
        block.rotated = 0;
        block.steps_moved = 0;
        return block;
    } else {
        block_shape block;
        block.kind_of_block = 5;
        block.isDone = 0;
        SDL_Color color = {238, 27, 185, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 200;
        block.x = (rand()%9+1)*50;
        block.rotated = 0;
        block.steps_moved = 0;
        return block;
    }
}

int can_move_right(block_shape *block, grid_elem grid[15][10], int steps){
    int x, y;
    int max_pos = block->shape[0].x + block->size;
    for(int i = 1; i < 4; i++){
        if((block->shape[i].x + block->size) > max_pos) max_pos = block->shape[i].x + block->size;
    }

    for(int i = 0; i < 4; i++){
        y = (block->shape[i].y - 150)/block->size;
        x = (block->shape[i].x + block->size)/block->size;
        if(grid[y][x].used == 1) return 0;
    }

    if(max_pos < WIDTH - (steps - 1)*block->size) return 1;
    return 0;
}

int can_move_left(block_shape *block, grid_elem grid[15][10], int steps){
    int x, y;
    int min_pos = block->shape[0].x;
    for(int i = 1; i < 4; i++){
        if(block->shape[i].x < min_pos) min_pos = block->shape[i].x;
    }

    for(int i = 0; i < 4; i++){
        y = (block->shape[i].y - 150)/block->size;
        x = (block->shape[i].x - block->size)/block->size;
        if(grid[y][x].used == 1) return 0;
    }

    if(min_pos > 0 + (steps - 1)*block->size) return 1;
    return 0;
}

//moving block left and right
void move_to_sides(block_shape *block, int side, int vel, grid_elem grid[15][10]){
    if(side == 0){
        if(can_move_left(block, grid, 1)) block->x -= vel;
    } else if(side == 1){
        if(can_move_right(block, grid, 1)) block->x += vel;
    }
}

void can_move_down(block_shape *block, grid_elem grid[15][10], int vel, int *score){
    int x, y;
    int max_pos = block->shape[0].y + block->size;
    for(int i = 1; i < 4; i++){
        if((block->shape[i].y + block->size) > max_pos) max_pos = block->shape[i].y + block->size;
    }

    if(max_pos == HEIGHT){
        for(int i = 0; i < 4; i++){
            x = block->shape[i].x/block->size;
            y = (block->shape[i].y - 150)/block->size;
            grid[y][x].shape.x = block->shape[i].x;
            grid[y][x].shape.y = block->shape[i].y;
            grid[y][x].shape.w = block->size;
            grid[y][x].shape.h = block->size;
            grid[y][x].used = 1;
            SDL_Color color = block->block_color;
            grid[y][x].block_color = color;
        }
        block->isDone = 1;
    } else {
        for(int i = 0; i < 4; i++){
            y = (block->shape[i].y - 100)/block->size;
            x = block->shape[i].x/block->size;
            if(grid[y][x].used == 1){
                for(int j = 0; j < 4; j++){
                    x = block->shape[j].x/block->size;
                    y = (block->shape[j].y - 150)/block->size;
                    grid[y][x].shape.x = block->shape[j].x;
                    grid[y][x].shape.y = block->shape[j].y;
                    grid[y][x].shape.w = block->size;
                    grid[y][x].shape.h = block->size;
                    grid[y][x].used = 1;
                    SDL_Color color = block->block_color;
                    grid[y][x].block_color = color;
                    block->isDone = 1;
                }
                break;
            }
        }
    }
    if(block->isDone == 1){
        *score += 25;
        return;
    }
    if(max_pos < HEIGHT) block->y += vel;
}

void rotate(block_shape *block, grid_elem grid[15][10]){
    int r = block->rotated;
    switch(block->kind_of_block){
    case 1:
        if(r == 0 && can_move_right(block, grid, 2) && can_move_left(block, grid, 1)) block->rotated += 90;
        else if(r == 0 && !can_move_right(block, grid, 2) && can_move_right(block, grid, 1)){ block->rotated += 90; block->x -= 50; block->steps_moved = -1; }
        else if(r == 0 && !can_move_right(block, grid, 1)){ block->rotated += 90; block->x -= 100; block->steps_moved = -2; }
        else if(r == 0 && !can_move_left(block, grid, 1)){ block->rotated += 90; block->x += 50; block->steps_moved = 1; }
        else if(r == 90 && block->steps_moved == -2) { block->rotated += 90; block->x += 100; block->steps_moved = 0; }
        else if(r == 90 && block->steps_moved == -1) { block->rotated += 90; block->x += 50; block->steps_moved = 0; }
        else if(r == 90 && block->steps_moved == 1) { block->rotated += 90; block->x -= 50; block->steps_moved = 0; }
        else if(r == 90 && block->steps_moved == 0) block->rotated += 90;
        else if(r == 180 && !can_move_right(block, grid, 1)) { block->rotated += 90; block->x -= 50; block->steps_moved = -1; }
        else if(r == 180 && !can_move_left(block, grid, 1)){ block->rotated += 90; block->x += 100; block->steps_moved = 2; }
        else if(r == 180 && can_move_left(block, grid, 1) && !can_move_left(block, grid, 2)){ block->rotated += 90; block->x += 50; block->steps_moved = 1; }
        else if(r == 180 && can_move_right(block, grid, 1)) block->rotated += 90;
        else if(r == 270 && block->steps_moved == -1) { block->rotated = 0; block->x += 50; block->steps_moved = 0; }
        else if(r == 270 && block->steps_moved == 0) block->rotated = 0;
        else if(r == 270 && block->steps_moved == 1) { block->rotated = 0; block->x -= 50; block->steps_moved = 0; }
        else if(r == 270 && block->steps_moved == 2) { block->rotated = 0; block->x -= 100; block->steps_moved = 0; }
        break;
    case 2:
        if(r == 0 && can_move_left(block, grid, 1)) block->rotated += 90;
        else if(r == 0 && !can_move_left(block, grid, 1)) { block->rotated += 90; block->x += 50; block->steps_moved = 1; }
        else if(r == 90) block->rotated += 90;
        else if(r == 180 && can_move_right(block, grid, 1)) block->rotated += 90;
        else if(r == 180 && !can_move_right(block, grid, 1)) { block->rotated += 90; block->x -= 50; block->steps_moved = -1; }
        else if(r == 270 && block->steps_moved == 1) { block->rotated = 0; block->x -= 50; block->steps_moved = 0;}
        else if(r == 270 && block->steps_moved == -1) { block->rotated = 0; block->steps_moved = 0;}
        else if(r == 270 && block->steps_moved == 0) block->rotated = 0;
        break;
    case 4:
        if(r == 0 && block->steps_moved == 0) block->rotated += 90;
        else if(r == 0 && block->steps_moved == -1) { block->rotated += 90; block->steps_moved = 0; }
        else if(r == 90 && can_move_left(block, grid, 1))block->rotated += 90;
        else if(r == 90 && !can_move_left(block, grid, 1)){ block->rotated += 90; block->x += 50; block->steps_moved = 1; }
        else if(r == 180 && block->steps_moved == 0) block->rotated += 90;
        else if(r == 180 && block->steps_moved == 1) { block->rotated += 90; block->steps_moved = 0;}
        else if(r == 270 && can_move_right(block, grid, 1)) block->rotated = 0;
        else if(r == 270 && !can_move_right(block, grid, 1)) { block->rotated = 0; block->x -= 50; block->steps_moved = -1; }
        break;
    case 5:
        if(r == 0 && block->steps_moved == 0) block->rotated += 90;
        else if(r == 0 && block->steps_moved == -1) { block->rotated += 90;  block->steps_moved = 0; }
        else if(r == 90 && can_move_left(block, grid, 1))block->rotated += 90;
        else if(r == 90 && !can_move_left(block, grid, 1)){ block->rotated += 90; block->x += 50; block->steps_moved = 1; }
        else if(r == 180 && block->steps_moved == 0) block->rotated += 90;
        else if(r == 180 && block->steps_moved == 1) { block->rotated += 90;  block->steps_moved = 0; }
        else if(r == 270 && can_move_right(block, grid, 1)) block->rotated = 0;
        else if(r == 270 && !can_move_right(block, grid, 1)) { block->rotated = 0; block->x -= 50; block->steps_moved = -1; }
        break;
    case 6:
        if(r == 0 && block->steps_moved == 0) block->rotated += 90;
        else if(r == 0 && block->steps_moved == -1) { block->rotated += 90;  block->steps_moved = 0; }
        else if(r == 90 && can_move_left(block, grid, 1))block->rotated += 90;
        else if(r == 90 && !can_move_left(block, grid, 1)){ block->rotated += 90; block->x += 50; block->steps_moved = 1; }
        else if(r == 180 && block->steps_moved == 0) block->rotated += 90;
        else if(r == 180 && block->steps_moved == 1) { block->rotated += 90;  block->steps_moved = 0; }
        else if(r == 270 && can_move_right(block, grid, 1)) block->rotated = 0;
        else if(r == 270 && !can_move_right(block, grid, 1)) { block->rotated = 0; block->x -= 50; block->steps_moved = -1; }
        break;
    case 7:
        if(r == 0 && can_move_right(block, grid, 2)) block->rotated += 90;
        else if(r == 0 && !can_move_right(block, grid, 1)) { block-> rotated += 90; block->x -= 100; block->steps_moved = -2; }
        else if(r == 0 && !can_move_right(block, grid, 2) && can_move_right(block, grid, 1)) { block-> rotated += 90; block->x -= 50; block->steps_moved = -1; }
        else if(r == 90 && block->steps_moved == 0) block->rotated += 90;
        else if(r == 90 && block->steps_moved == -2) { block->rotated += 90; block->x += 50; }
        else if(r == 90 && block->steps_moved == -1) { block->rotated += 90; block->x += 50; block->steps_moved = 0; }
        else if(r == 180 && block->steps_moved == -2) { block->rotated += 90; block->x += 50; block->steps_moved = 0; }
        else if(r == 180 && can_move_left(block, grid, 2)) block->rotated += 90;
        else if(r == 180 && !can_move_left(block, grid, 1)) { block->rotated += 90; block->x += 100; block->steps_moved = 2; }
        else if(r == 180 && can_move_left(block, grid, 1) && !can_move_left(block, grid, 2)) { block->rotated += 90; block->x += 50; block->steps_moved = 1; }
        else if(r == 270 && block->steps_moved == 0) block->rotated = 0;
        else if(r == 270 && block->steps_moved == 2) { block->rotated = 0; block->x -= 50; block->steps_moved = 0; }
        else if(r == 270 && block->steps_moved == 1) { block->rotated = 0; block->x -= 50; block->steps_moved = 0; }
        break;
    }
}

int gameOver(block_shape *block, grid_elem grid[15][10]){
    for(int i = 0; i < 10; i++){
        if(grid[0][i].used == 1) return  1;
    }
    return 0;
}

void destroyLine(grid_elem grid[15][10], int *score){
    int doneLines = 0;
    for(int i = 0; i < 15; i++){
        int line_used_elems = 0;
        for(int j = 0; j < 10; j++){
            if(grid[i][j].used){
                line_used_elems++;
            }
        }
        if(line_used_elems == 10){
            doneLines++;
            for(int y = i; y > 0; y--){
                for(int x = 0; x < 10; x++){
                    grid[y][x].used = grid[y-1][x].used;
                    SDL_Color color = grid[y-1][x].block_color;
                    grid[y][x].block_color = color;
                }
            }
            *score += 100;
        }
    }
    if(doneLines == 4){
        *score += 200;
    }
}
