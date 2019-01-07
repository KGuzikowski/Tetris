#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "logic.h"
#include "graphic.h"

//generating random block
block_shape generate_block(){
    int block_num;
    block_num = (rand()%7) + 1;

    if(block_num == 1){
        block_shape block;
        block.kind_of_block = 1;
        block.isDone = 0;
        SDL_Color color = {234, 184, 46, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 150;
        block.x = (rand()%10)*50;
        return block;
    } else if(block_num == 2){
        block_shape block;
        block.kind_of_block = 2;
        block.isDone = 0;
        SDL_Color color = {48, 223, 56, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 150;
        block.x = (rand()%9)*50;
        return block;
    } else if(block_num == 3){
        block_shape block;
        block.kind_of_block = 3;
        block.isDone = 0;
        SDL_Color color = {202, 65, 28, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 150;
        block.x = (rand()%9)*50;
        return block;
    } else if(block_num == 4){
        block_shape block;
        block.kind_of_block = 4;
        block.isDone = 0;
        SDL_Color color = {28, 202, 199, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 150;
        block.x = (rand()%8+2)*50;
        return block;
    } else if(block_num == 5){
        block_shape block;
        block.kind_of_block = 5;
        block.isDone = 0;
        SDL_Color color = {238, 27, 185, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 150;
        block.x = (rand()%9+1)*50;
        return block;
    } else if(block_num == 6){
        block_shape block;
        block.kind_of_block = 6;
        block.isDone = 0;
        SDL_Color color = {41, 34, 236, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 150;
        block.x = (rand()%8)*50;
        return block;
    } else if(block_num == 7){
        block_shape block;
        block.kind_of_block = 7;
        block.isDone = 0;
        SDL_Color color = {242, 162, 105, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 150;
        int x = (rand()%10);
        if(x < 2) x += 1;
        block.x = (rand()%9+1)*50;
        return block;
    } else {
        block_shape block;
        block.kind_of_block = 5;
        block.isDone = 0;
        SDL_Color color = {238, 27, 185, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 150;
        block.x = (rand()%9+1)*50;
        return block;
    }
}

//moving block left and right
void move_to_sides(block_shape *block, int side, int vel){
    if(side == 0){
        int min_pos = block->shape[0].x;
        for(int i = 1; i < 4; i++){
            if(block->shape[i].x < min_pos) min_pos = block->shape[i].x;
        }
        if(min_pos > 0) block->x -= vel;
    } else if(side == 1){
        int max_pos = block->shape[0].x + block->size;
        for(int i = 1; i < 4; i++){
            if((block->shape[i].x + block->size) > max_pos) max_pos = block->shape[i].x + block->size;
        }
        if(max_pos < 500) block->x += vel;
    }
}

void move_down(block_shape *block, int vel){
    int max_pos = block->shape[0].y + block->size;
    for(int i = 1; i < 4; i++){
        if((block->shape[i].y + block->size) > max_pos) max_pos = block->shape[i].y + block->size;
    }
    if(max_pos < 900) block->y += vel;
}
