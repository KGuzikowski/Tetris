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
        block.x = (rand()%10) * 50;
        return block;
    } else if(block_num == 2){
        block_shape block;
        block.kind_of_block = 2;
        block.isDone = 0;
        SDL_Color color = {48, 223, 56, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 150;
        block.x = (rand()%10) * 50;
        return block;
    } else if(block_num == 3){
        block_shape block;
        block.kind_of_block = 3;
        block.isDone = 0;
        SDL_Color color = {202, 65, 28, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 150;
        block.x = (rand()%10) * 50;
        return block;
    } else if(block_num == 4){
        block_shape block;
        block.kind_of_block = 4;
        block.isDone = 0;
        SDL_Color color = {28, 202, 199, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 150;
        int x = (rand()%10) * 50;
        if(x < 3) x += 2;
        block.x = x;
        return block;
    } else if(block_num == 5){
        block_shape block;
        block.kind_of_block = 5;
        block.isDone = 0;
        SDL_Color color = {238, 27, 185, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 150;
        int x = (rand()%10) * 50;
        if(x < 2) x += 1;
        block.x = x;
        return block;
    } else if(block_num == 6){
        block_shape block;
        block.kind_of_block = 6;
        block.isDone = 0;
        SDL_Color color = {41, 34, 236, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 150;
        block.x = (rand()%10) * 50;
        return block;
    } else if(block_num == 7){
        block_shape block;
        block.kind_of_block = 7;
        block.isDone = 0;
        SDL_Color color = {242, 162, 105, 0};
        block.block_color = color;
        block.size = 50;
        block.y = 150;
        int x = (rand()%10) * 50;
        if(x < 2) x += 1;
        block.x = x;
        return block;
    }
}
