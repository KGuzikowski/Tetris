#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include "graphic.h"

#define WIDTH 500
#define HEIGHT 900

void set_bg(SDL_Renderer *renderer){
    //Set background color
    SDL_SetRenderDrawColor(renderer, 134, 93, 146, 0);
    //Clear the screen
    SDL_RenderClear(renderer);
    //Set top bar
    SDL_SetRenderDrawColor(renderer, 88, 62, 96, 0);
    SDL_Rect top_bar = {0, 0, WIDTH, 120};
    SDL_RenderFillRect(renderer, &top_bar);
}

void set_text(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *title_font, TTF_Font *score_font, TTF_Font *score_num_font, int score){
    SDL_Color title_color= {255, 255, 255, 0};
    SDL_Surface *title = TTF_RenderText_Solid(title_font, "TETRIS", title_color);
    if(!title){
        printf("error creating title title surface: %s\n", SDL_GetError());
        TTF_CloseFont(title_font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    SDL_Texture *title_texture = SDL_CreateTextureFromSurface(renderer, title);
    SDL_FreeSurface(title);
    if(!title_texture){
        printf("error creating title texture: %s\n", SDL_GetError());
        TTF_CloseFont(title_font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    title = TTF_RenderText_Solid(score_font, "Wynik: ", title_color);
    if(!title){
        printf("error creating score_title surface: %s\n", SDL_GetError());
        TTF_CloseFont(score_font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    SDL_Texture *score_title_texture = SDL_CreateTextureFromSurface(renderer, title);
    SDL_FreeSurface(title);
    if(!score_title_texture){
        printf("error creating score_title texture: %s\n", SDL_GetError());
        TTF_CloseFont(score_font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    char wynik[6];
    sprintf(wynik, "%d", score);

    title = TTF_RenderText_Solid(score_num_font, wynik, title_color);
    if(!title){
        printf("error creating score num title surface: %s\n", SDL_GetError());
        TTF_CloseFont(score_font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    SDL_Texture *score_num = SDL_CreateTextureFromSurface(renderer, title);
    SDL_FreeSurface(title);
    if(!score_num){
        printf("error creating score_num texture: %s\n", SDL_GetError());
        TTF_CloseFont(score_num_font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    SDL_Rect dest;
    SDL_Rect dest2;
    SDL_Rect dest3;

    //Get dimensions of title texture
    SDL_QueryTexture(title_texture, NULL, NULL, &dest.w, &dest.h);
    dest.x = (WIDTH - dest.w)/2;
    dest.y = (60 - dest.h)/2;

    //Get dimensions of title score texture
    SDL_QueryTexture(score_title_texture, NULL, NULL, &dest2.w, &dest2.h);
    dest2.x = (WIDTH - dest2.w)/2;
    dest2.y = (140 - dest2.h)/2;

    //Get dimensions of title score texture
    SDL_QueryTexture(score_num, NULL, NULL, &dest3.w, &dest3.h);
    dest3.x = (WIDTH - dest3.w)/2;
    dest3.y = (200 - dest3.h)/2;

    SDL_RenderCopy(renderer, title_texture, NULL, &dest);
    SDL_RenderCopy(renderer, score_title_texture, NULL, &dest2);
    SDL_RenderCopy(renderer, score_num, NULL, &dest3);
    SDL_DestroyTexture(title_texture);
    SDL_DestroyTexture(score_title_texture);
    SDL_DestroyTexture(score_num);
}

void drawI_shape(SDL_Renderer *renderer, int x, int y){
    int size = 50;
    I_shape fshape;
    //1 block
    fshape.shape[0].x = x;
    fshape.shape[0].y = y;
    fshape.shape[0].w = size;
    fshape.shape[0].h = size;
    //2 block
    fshape.shape[1].x = x;
    fshape.shape[1].y = y + size;
    fshape.shape[1].w = size;
    fshape.shape[1].h = size;
    //3 block
    fshape.shape[2].x = x;
    fshape.shape[2].y = y + 2*size;
    fshape.shape[2].w = size;
    fshape.shape[2].h = size;
    //4 block
    fshape.shape[3].x = x;
    fshape.shape[3].y = y + 3*size;
    fshape.shape[3].w = size;
    fshape.shape[3].h = size;

    //render filled blocks
    SDL_SetRenderDrawColor(renderer, 234, 184, 46, 0);
    SDL_RenderFillRect(renderer, &fshape.shape[0]);
    SDL_RenderFillRect(renderer, &fshape.shape[1]);
    SDL_RenderFillRect(renderer, &fshape.shape[2]);
    SDL_RenderFillRect(renderer, &fshape.shape[3]);
    //render block's outlines
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderDrawRect(renderer, &fshape.shape[0]);
    SDL_RenderDrawRect(renderer, &fshape.shape[1]);
    SDL_RenderDrawRect(renderer, &fshape.shape[2]);
    SDL_RenderDrawRect(renderer, &fshape.shape[3]);
}

void drawL_shape(SDL_Renderer *renderer, int x, int y){
    int size = 50;
    I_shape fshape;
    //1 block
    fshape.shape[0].x = x;
    fshape.shape[0].y = y;
    fshape.shape[0].w = size;
    fshape.shape[0].h = size;
    //2 block
    fshape.shape[1].x = x;
    fshape.shape[1].y = y + size;
    fshape.shape[1].w = size;
    fshape.shape[1].h = size;
    //3 block
    fshape.shape[2].x = x;
    fshape.shape[2].y = y + 2*size;
    fshape.shape[2].w = size;
    fshape.shape[2].h = size;
    //4 block
    fshape.shape[3].x = x + size;
    fshape.shape[3].y = y + 2*size;
    fshape.shape[3].w = size;
    fshape.shape[3].h = size;

    //render filled blocks
    SDL_SetRenderDrawColor(renderer, 48, 223, 56, 0);
    SDL_RenderFillRect(renderer, &fshape.shape[0]);
    SDL_RenderFillRect(renderer, &fshape.shape[1]);
    SDL_RenderFillRect(renderer, &fshape.shape[2]);
    SDL_RenderFillRect(renderer, &fshape.shape[3]);
    //render block's outlines
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderDrawRect(renderer, &fshape.shape[0]);
    SDL_RenderDrawRect(renderer, &fshape.shape[1]);
    SDL_RenderDrawRect(renderer, &fshape.shape[2]);
    SDL_RenderDrawRect(renderer, &fshape.shape[3]);
}

void drawR_shape(SDL_Renderer *renderer, int x, int y){
    int size = 50;
    I_shape fshape;
    //1 block
    fshape.shape[0].x = x;
    fshape.shape[0].y = y;
    fshape.shape[0].w = size;
    fshape.shape[0].h = size;
    //2 block
    fshape.shape[1].x = x + size;
    fshape.shape[1].y = y;
    fshape.shape[1].w = size;
    fshape.shape[1].h = size;
    //3 block
    fshape.shape[2].x = x;
    fshape.shape[2].y = y + size;
    fshape.shape[2].w = size;
    fshape.shape[2].h = size;
    //4 block
    fshape.shape[3].x = x + size;
    fshape.shape[3].y = y + size;
    fshape.shape[3].w = size;
    fshape.shape[3].h = size;

    //render filled blocks
    SDL_SetRenderDrawColor(renderer, 202, 65, 28, 0);
    SDL_RenderFillRect(renderer, &fshape.shape[0]);
    SDL_RenderFillRect(renderer, &fshape.shape[1]);
    SDL_RenderFillRect(renderer, &fshape.shape[2]);
    SDL_RenderFillRect(renderer, &fshape.shape[3]);
    //render block's outlines
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderDrawRect(renderer, &fshape.shape[0]);
    SDL_RenderDrawRect(renderer, &fshape.shape[1]);
    SDL_RenderDrawRect(renderer, &fshape.shape[2]);
    SDL_RenderDrawRect(renderer, &fshape.shape[3]);
}

void drawS_shape(SDL_Renderer *renderer, int x, int y){
    int size = 50;
    I_shape fshape;
    //1 block
    fshape.shape[0].x = x;
    fshape.shape[0].y = y;
    fshape.shape[0].w = size;
    fshape.shape[0].h = size;
    //2 block
    fshape.shape[1].x = x + size;
    fshape.shape[1].y = y;
    fshape.shape[1].w = size;
    fshape.shape[1].h = size;
    //3 block
    fshape.shape[2].x = x + size;
    fshape.shape[2].y = y - size;
    fshape.shape[2].w = size;
    fshape.shape[2].h = size;
    //4 block
    fshape.shape[3].x = x + 2*size;
    fshape.shape[3].y = y - size;
    fshape.shape[3].w = size;
    fshape.shape[3].h = size;

    //render filled blocks
    SDL_SetRenderDrawColor(renderer, 28, 202, 199, 0);
    SDL_RenderFillRect(renderer, &fshape.shape[0]);
    SDL_RenderFillRect(renderer, &fshape.shape[1]);
    SDL_RenderFillRect(renderer, &fshape.shape[2]);
    SDL_RenderFillRect(renderer, &fshape.shape[3]);
    //render block's outlines
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderDrawRect(renderer, &fshape.shape[0]);
    SDL_RenderDrawRect(renderer, &fshape.shape[1]);
    SDL_RenderDrawRect(renderer, &fshape.shape[2]);
    SDL_RenderDrawRect(renderer, &fshape.shape[3]);
}

void drawT_shape(SDL_Renderer *renderer, int x, int y){
    int size = 50;
    I_shape fshape;
    //1 block
    fshape.shape[0].x = x;
    fshape.shape[0].y = y;
    fshape.shape[0].w = size;
    fshape.shape[0].h = size;
    //2 block
    fshape.shape[1].x = x;
    fshape.shape[1].y = y + size;
    fshape.shape[1].w = size;
    fshape.shape[1].h = size;
    //3 block
    fshape.shape[2].x = x - size;
    fshape.shape[2].y = y + size;
    fshape.shape[2].w = size;
    fshape.shape[2].h = size;
    //4 block
    fshape.shape[3].x = x + size;
    fshape.shape[3].y = y + size;
    fshape.shape[3].w = size;
    fshape.shape[3].h = size;

    //render filled blocks
    SDL_SetRenderDrawColor(renderer, 238, 27, 185, 0);
    SDL_RenderFillRect(renderer, &fshape.shape[0]);
    SDL_RenderFillRect(renderer, &fshape.shape[1]);
    SDL_RenderFillRect(renderer, &fshape.shape[2]);
    SDL_RenderFillRect(renderer, &fshape.shape[3]);
    //render block's outlines
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderDrawRect(renderer, &fshape.shape[0]);
    SDL_RenderDrawRect(renderer, &fshape.shape[1]);
    SDL_RenderDrawRect(renderer, &fshape.shape[2]);
    SDL_RenderDrawRect(renderer, &fshape.shape[3]);
}
