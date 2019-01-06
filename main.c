#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include "graphic.h"

#define WIDTH 500
#define HEIGHT 800

int main(int argc, char *argv[]){
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

    TTF_Font *title_font = TTF_OpenFont("roboto.ttf", 70);
    if(title_font = NULL){
        printf("Error openint title_font: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    TTF_Font *score_font = TTF_OpenFont("roboto.ttf", 35);
    if(title_font = NULL){
        printf("Error openint score_font: %s\n", TTF_GetError());
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
            if(event.type == SDL_QUIT){
                isOpen = 0;
            }
        }

        //set background
        set_bg(renderer);

        //set title text
        set_text(window, renderer, title_font, score_font);

        //draw
        SDL_RenderPresent(renderer);
    }

    SDL_FreeSurface(title);
    TTF_CloseFont(score_font);
    TTF_CloseFont(title_font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}
