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
    int score = 0;
    int x_pos, y_pos = 120;

    //generating random y_pos
    srand(time(NULL));
    x_pos = (rand()%WIDTH) + 1;

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
    int isOpen = 1;
    while(isOpen){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                isOpen = 0;
                break;
            }
        }

        //set background
        set_bg(renderer);

        //set title text
        set_text(window, renderer, title_font, score_font, score_num_font, score);

        /*SDL_Rect rectToDraw = {100,100,100,100};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &rectToDraw);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &rectToDraw);*/

        /*drawI_shape(renderer, x_pos, y_pos);
        drawL_shape(renderer, 200, 200);
        drawR_shape(renderer, 200, 200);
        drawS_shape(renderer, 200, 200);*/
        drawT_shape(renderer, x_pos, y_pos);

        //draw
        SDL_RenderPresent(renderer);

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
