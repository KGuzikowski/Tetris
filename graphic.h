#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

typedef struct{
    SDL_Rect shape[4];
    int isDone;
    int kind_of_block;
    SDL_Color block_color;
    int x, y;
    int size;
    int rotated;
} block_shape;

typedef struct{
    SDL_Rect shape;
    SDL_Color block_color;
    int used;
} grid_elem;

grid_elem grid[15][10];

void set_bg(SDL_Renderer *renderer);
void set_text(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *title_font, TTF_Font *score_font, TTF_Font *score_num_font, int score);
void set_grid(SDL_Renderer *renderer);

void draw_elemsGrid(grid_elem grid[15][10], SDL_Renderer *renderer);

void draw_block(SDL_Renderer *renderer, block_shape *fshape);

void drawI_shape(SDL_Renderer *renderer, block_shape *fshape);
void drawL_shape(SDL_Renderer *renderer, block_shape *fshape);
void drawR_shape(SDL_Renderer *renderer, block_shape *fshape);
void drawS_shape(SDL_Renderer *renderer, block_shape *fshape);
void drawT_shape(SDL_Renderer *renderer, block_shape *fshape);
void drawZ_shape(SDL_Renderer *renderer, block_shape *fshape);
void drawJ_shape(SDL_Renderer *renderer, block_shape *fshape);

#endif // GRAPHIC_H_INCLUDED
