#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include "graphic.h"

#define WIDTH 500
#define HEIGHT 900

int main(int argc, char *argv[]){
    //variables
    int isOpen = 1;
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;
    int delay = 900;
    int vel = 50;
    int count = 1;
    int score = 0;
    int x_pos, y_pos = 150;

    //generating random y_pos
    srand(time(NULL));
    x_pos = (rand()%10) * 50;

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

    TTF_Font *title_font = TTF_OpenFont("font/roboto.ttf", 60);
    if(title_font == NULL){
        printf("Error openint title_font: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font *score_font = TTF_OpenFont("font/roboto.ttf", 30);
    if(score_font == NULL){
        printf("Error openint score_font: %s\n", TTF_GetError());
        TTF_CloseFont(title_font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font *score_num_font = TTF_OpenFont("font/roboto.ttf", 30);
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
                    up = 1;
                    break;
                case SDL_SCANCODE_LEFT:
                case SDL_SCANCODE_A:
                    x_pos -= vel;
                    break;
                case SDL_SCANCODE_DOWN:
                case SDL_SCANCODE_S:
                    y_pos += vel;
                    break;
                case SDL_SCANCODE_RIGHT:
                case SDL_SCANCODE_D:
                    x_pos += vel;
                    break;
                }
                break;
            }
        }

        //set background
        set_bg(renderer);

        //set title text
        set_text(window, renderer, title_font, score_font, score_num_font, score);

        /*drawI_shape(renderer, x_pos, y_pos);
        drawL_shape(renderer, x_pos, y_pos);
        drawR_shape(renderer, x_pos, y_pos);
        drawS_shape(renderer, x_pos, y_pos);*/

        //block animation
        if(count%70 == 0) y_pos += vel;
        //if(left && !right) x_pos -= vel;
        //if(right && !left) x_pos += vel;
        //if(down) y_pos += vel;

        drawT_shape(renderer, x_pos, y_pos);

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
