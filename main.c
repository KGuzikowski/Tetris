#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include "graphic.h"
#include "logic.h"

#define WIDTH 500
#define HEIGHT 900
#define BLOCK_SIZE 50
#define VEL 50

int main(int argc, char *argv[]){
    //variables
    int isOpen = 1;
    int count = 1;
    int score = 0;

    srand(time(NULL));

    //SDL initialization
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    //Window initialization
    SDL_Window *window = SDL_CreateWindow("Tetris by Karol Guzikowski",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WIDTH, HEIGHT, 0);
    if(!window){
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flags);
    if(!renderer){
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if(TTF_Init() == -1){
        printf("Error initializing TTF: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font *title_font = TTF_OpenFont("font/roboto.ttf", 70);
    if(title_font == NULL){
        printf("Error openint title_font: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font *score_font = TTF_OpenFont("font/roboto.ttf", 40);
    if(score_font == NULL){
        printf("Error openint score_font: %s\n", TTF_GetError());
        TTF_CloseFont(title_font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font *score_num_font = TTF_OpenFont("font/roboto.ttf", 50);
    if(score_num_font == NULL){
        printf("Error openint score_num_font: %s\n", TTF_GetError());
        TTF_CloseFont(score_font);
        TTF_CloseFont(title_font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    //initialize grid array
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 10; j++){
            grid[i][j].used = 0;
        }
    }

    //generating random block
    block_shape block = generate_block();

    //Game loop
    while(isOpen){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                isOpen = 0;
                break;
            case(SDL_KEYDOWN):
                switch(event.key.keysym.scancode){
                case SDL_SCANCODE_UP:
                case SDL_SCANCODE_W:
                    block.isDone = 1;
                    break;
                case SDL_SCANCODE_LEFT:
                case SDL_SCANCODE_A:
                    move_to_sides(&block, 0, VEL);
                    break;
                case SDL_SCANCODE_DOWN:
                case SDL_SCANCODE_S:
                    move_down(&block, VEL);
                    break;
                case SDL_SCANCODE_RIGHT:
                case SDL_SCANCODE_D:
                    move_to_sides(&block, 1, VEL);
                    break;
                }
                break;
            }
        }

        //set background
        set_bg(renderer);

        //set title text
        set_text(window, renderer, title_font, score_font, score_num_font, score);

        //block animation
        if(count%50 == 0 && block.isDone == 0) move_down(&block, VEL);

        //check if block can move
        can_move_down(&block, grid, VEL);

        //draw grid of done blocks
        draw_elemsGrid(grid, renderer);

        //draw block
        if(block.isDone) block = generate_block();
        else draw_block(renderer, &block);

        //set grid
        set_grid(renderer);

        //draw
        SDL_RenderPresent(renderer);
        count++;
    }

    TTF_CloseFont(score_num_font);
    TTF_CloseFont(score_font);
    TTF_CloseFont(title_font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}
