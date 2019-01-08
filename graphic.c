#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include "graphic.h"
#include "logic.h"

#define WIDTH 500
#define HEIGHT 900

void set_bg(SDL_Renderer *renderer){
    //Set background color
    SDL_SetRenderDrawColor(renderer, 134, 93, 146, 0);
    //Clear the screen
    SDL_RenderClear(renderer);
    //Set top bar
    SDL_SetRenderDrawColor(renderer, 88, 62, 96, 0);
    SDL_Rect top_bar = {0, 0, WIDTH, 150};
    SDL_RenderFillRect(renderer, &top_bar);
}

void set_grid(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    for(int i = 1; i <= 18; i++){
       SDL_RenderDrawLine(renderer, 0, (i*50 + 150), WIDTH, (i*50 + 150));
    }

    for(int j = 1; j <= 10; j++){
         SDL_RenderDrawLine(renderer, (j*50), 150, (j*50), HEIGHT);
    }
}

void set_text(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *title_font, TTF_Font *score_font, TTF_Font *score_num_font, int score){
    SDL_Color title_color = {255, 255, 255, 0};
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
    dest2.y = (160 - dest2.h)/2;

    //Get dimensions of title score texture
    SDL_QueryTexture(score_num, NULL, NULL, &dest3.w, &dest3.h);
    dest3.x = (WIDTH - dest3.w)/2;
    dest3.y = (240 - dest3.h)/2;

    SDL_RenderCopy(renderer, title_texture, NULL, &dest);
    SDL_RenderCopy(renderer, score_title_texture, NULL, &dest2);
    SDL_RenderCopy(renderer, score_num, NULL, &dest3);
    SDL_DestroyTexture(title_texture);
    SDL_DestroyTexture(score_title_texture);
    SDL_DestroyTexture(score_num);
}

void draw_elemsGrid(grid_elem grid[15][10], SDL_Renderer *renderer){
    int r, g, b, a;
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 10; j++){
            if(grid[i][j].used){
                r = grid[i][j].block_color.r;
                g = grid[i][j].block_color.g;
                b = grid[i][j].block_color.b;
                a = grid[i][j].block_color.a;
                SDL_SetRenderDrawColor(renderer, r, g, b, a);
                SDL_RenderFillRect(renderer, &grid[i][j].shape);
            }
        }
    }
}

void draw_block(SDL_Renderer *renderer, block_shape *fshape){
    switch(fshape->kind_of_block){
    case 1:
        drawI_shape(renderer, fshape);
        break;
    case 2:
        drawL_shape(renderer, fshape);
        break;
    case 3:
        drawR_shape(renderer, fshape);
        break;
    case 4:
        drawS_shape(renderer, fshape);
        break;
    case 5:
        drawT_shape(renderer, fshape);
        break;
    case 6:
        drawZ_shape(renderer, fshape);
        break;
    case 7:
        drawJ_shape(renderer, fshape);
        break;
    }
}

void drawI_shape(SDL_Renderer *renderer, block_shape *fshape){
    if(fshape->rotated == 0){
        //1 block
        fshape->shape[0].x = fshape->x;
        fshape->shape[0].y = fshape->y - 2*fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y - fshape->size;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x;
        fshape->shape[3].y = fshape->y + fshape->size;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 90){
        //1 block
        fshape->shape[0].x = fshape->x + 2*fshape->size;
        fshape->shape[0].y = fshape->y;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x + fshape->size;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x - fshape->size;
        fshape->shape[3].y = fshape->y;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 180){
        //1 block
        fshape->shape[0].x = fshape->x;
        fshape->shape[0].y = fshape->y + 2*fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y + fshape->size;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x;
        fshape->shape[3].y = fshape->y - fshape->size;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 270){
        //1 block
        fshape->shape[0].x = fshape->x - 2*fshape->size;
        fshape->shape[0].y = fshape->y;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x - fshape->size;;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x + fshape->size;
        fshape->shape[3].y = fshape->y;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    }

    //set color
    int r, g, b, a;
    r = fshape->block_color.r;
    g = fshape->block_color.g;
    b = fshape->block_color.b;
    a = fshape->block_color.a;
    //render filled blocks
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &fshape->shape[0]);
    SDL_RenderFillRect(renderer, &fshape->shape[1]);
    SDL_RenderFillRect(renderer, &fshape->shape[2]);
    SDL_RenderFillRect(renderer, &fshape->shape[3]);
}

void drawL_shape(SDL_Renderer *renderer, block_shape *fshape){
    if(fshape->rotated == 0){
        //1 block
        fshape->shape[0].x = fshape->x;
        fshape->shape[0].y = fshape->y - fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y + fshape->size;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x + fshape->size;
        fshape->shape[3].y = fshape->y + fshape->size;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 90){
        //1 block
        fshape->shape[0].x = fshape->x + fshape->size;
        fshape->shape[0].y = fshape->y;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x - fshape->size;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x - fshape->size;
        fshape->shape[3].y = fshape->y + fshape->size;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 180){
        //1 block
        fshape->shape[0].x = fshape->x;
        fshape->shape[0].y = fshape->y + fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y - fshape->size;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x - fshape->size;
        fshape->shape[3].y = fshape->y - fshape->size;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 270){
        //1 block
        fshape->shape[0].x = fshape->x - fshape->size;
        fshape->shape[0].y = fshape->y;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x + fshape->size;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x + fshape->size;
        fshape->shape[3].y = fshape->y - fshape->size;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    }

    //set color
    int r, g, b, a;
    r = fshape->block_color.r;
    g = fshape->block_color.g;
    b = fshape->block_color.b;
    a = fshape->block_color.a;
    //render filled blocks
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &fshape->shape[0]);
    SDL_RenderFillRect(renderer, &fshape->shape[1]);
    SDL_RenderFillRect(renderer, &fshape->shape[2]);
    SDL_RenderFillRect(renderer, &fshape->shape[3]);
}

void drawR_shape(SDL_Renderer *renderer, block_shape *fshape){
     if(fshape->rotated == 0){
        //1 block
        fshape->shape[0].x = fshape->x - fshape->size;
        fshape->shape[0].y = fshape->y - fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y - fshape->size;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x - fshape->size;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x;
        fshape->shape[3].y = fshape->y;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
     } else if(fshape->rotated == 90){
        //1 block
        fshape->shape[0].x = fshape->x + fshape->size;
        fshape->shape[0].y = fshape->y - fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x + fshape->size;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y - fshape->size;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x;
        fshape->shape[3].y = fshape->y;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
     } else if(fshape->rotated == 180){
        //1 block
        fshape->shape[0].x = fshape->x + fshape->size;
        fshape->shape[0].y = fshape->y + fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y - fshape->size;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x + fshape->size;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x;
        fshape->shape[3].y = fshape->y;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
     } else if(fshape->rotated == 270){
        //1 block
        fshape->shape[0].x = fshape->x - fshape->size;
        fshape->shape[0].y = fshape->y + fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x - fshape->size;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y + fshape->size;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x;
        fshape->shape[3].y = fshape->y;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
     }

    //set color
    int r, g, b, a;
    r = fshape->block_color.r;
    g = fshape->block_color.g;
    b = fshape->block_color.b;
    a = fshape->block_color.a;
    //render filled blocks
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &fshape->shape[0]);
    SDL_RenderFillRect(renderer, &fshape->shape[1]);
    SDL_RenderFillRect(renderer, &fshape->shape[2]);
    SDL_RenderFillRect(renderer, &fshape->shape[3]);
}

void drawS_shape(SDL_Renderer *renderer, block_shape *fshape){
    if(fshape->rotated == 0){
       //1 block
        fshape->shape[0].x = fshape->x + fshape->size;
        fshape->shape[0].y = fshape->y - fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y - fshape->size;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x - fshape->size;
        fshape->shape[3].y = fshape->y;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 90){
       //1 block
        fshape->shape[0].x = fshape->x + fshape->size;
        fshape->shape[0].y = fshape->y + fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x + fshape->size;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x;
        fshape->shape[3].y = fshape->y - fshape->size;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 180){
       //1 block
        fshape->shape[0].x = fshape->x - fshape->size;
        fshape->shape[0].y = fshape->y + fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y + fshape->size;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x + fshape->size;
        fshape->shape[3].y = fshape->y;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 270){
       //1 block
        fshape->shape[0].x = fshape->x - fshape->size;
        fshape->shape[0].y = fshape->y - fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x - fshape->size;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x;
        fshape->shape[3].y = fshape->y + fshape->size;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    }

    //set color
    int r, g, b, a;
    r = fshape->block_color.r;
    g = fshape->block_color.g;
    b = fshape->block_color.b;
    a = fshape->block_color.a;
    //render filled blocks
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &fshape->shape[0]);
    SDL_RenderFillRect(renderer, &fshape->shape[1]);
    SDL_RenderFillRect(renderer, &fshape->shape[2]);
    SDL_RenderFillRect(renderer, &fshape->shape[3]);
}

void drawT_shape(SDL_Renderer *renderer, block_shape *fshape){
    if(fshape->rotated == 0){
        //1 block
        fshape->shape[0].x = fshape->x;
        fshape->shape[0].y = fshape->y - fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x - fshape->size;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x + fshape->size;
        fshape->shape[3].y = fshape->y;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 90){
        //1 block
        fshape->shape[0].x = fshape->x + fshape->size;
        fshape->shape[0].y = fshape->y;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y - fshape->size;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x;
        fshape->shape[3].y = fshape->y + fshape->size;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 180){
        //1 block
        fshape->shape[0].x = fshape->x;
        fshape->shape[0].y = fshape->y + fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x + fshape->size;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x - fshape->size;
        fshape->shape[3].y = fshape->y;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 270){
        //1 block
        fshape->shape[0].x = fshape->x - fshape->size;
        fshape->shape[0].y = fshape->y;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y + fshape->size;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x;
        fshape->shape[3].y = fshape->y - fshape->size;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    }

    //set color
    int r, g, b, a;
    r = fshape->block_color.r;
    g = fshape->block_color.g;
    b = fshape->block_color.b;
    a = fshape->block_color.a;
    //render filled blocks
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &fshape->shape[0]);
    SDL_RenderFillRect(renderer, &fshape->shape[1]);
    SDL_RenderFillRect(renderer, &fshape->shape[2]);
    SDL_RenderFillRect(renderer, &fshape->shape[3]);
}

void drawZ_shape(SDL_Renderer *renderer, block_shape *fshape){
    if(fshape->rotated == 0){
        //1 block
        fshape->shape[0].x = fshape->x - fshape->size;
        fshape->shape[0].y = fshape->y - fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y - fshape->size;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x + fshape->size;
        fshape->shape[3].y = fshape->y;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 90){
        //1 block
        fshape->shape[0].x = fshape->x + fshape->size;
        fshape->shape[0].y = fshape->y - fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x + fshape->size;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x;
        fshape->shape[3].y = fshape->y + fshape->size;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 180){
        //1 block
        fshape->shape[0].x = fshape->x + fshape->size;
        fshape->shape[0].y = fshape->y + fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y + fshape->size;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x - fshape->size;
        fshape->shape[3].y = fshape->y;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 270){
        //1 block
        fshape->shape[0].x = fshape->x - fshape->size;
        fshape->shape[0].y = fshape->y + fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x - fshape->size;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x;
        fshape->shape[3].y = fshape->y - fshape->size;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    }

    //set color
    int r, g, b, a;
    r = fshape->block_color.r;
    g = fshape->block_color.g;
    b = fshape->block_color.b;
    a = fshape->block_color.a;
    //render filled blocks
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &fshape->shape[0]);
    SDL_RenderFillRect(renderer, &fshape->shape[1]);
    SDL_RenderFillRect(renderer, &fshape->shape[2]);
    SDL_RenderFillRect(renderer, &fshape->shape[3]);
}

void drawJ_shape(SDL_Renderer *renderer, block_shape *fshape){
    if(fshape->rotated == 0){
        //1 block
        fshape->shape[0].x = fshape->x;
        fshape->shape[0].y = fshape->y - 2*fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y - fshape->size;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x - fshape->size;
        fshape->shape[3].y = fshape->y;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 90){
        //1 block
        fshape->shape[0].x = fshape->x + 2*fshape->size;
        fshape->shape[0].y = fshape->y;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x + fshape->size;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x;
        fshape->shape[3].y = fshape->y - fshape->size;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 180){
        //1 block
        fshape->shape[0].x = fshape->x;
        fshape->shape[0].y = fshape->y + 2*fshape->size;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x;
        fshape->shape[1].y = fshape->y + fshape->size;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x + fshape->size;
        fshape->shape[3].y = fshape->y;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    } else if(fshape->rotated == 270){
        //1 block
        fshape->shape[0].x = fshape->x - 2*fshape->size;
        fshape->shape[0].y = fshape->y;
        fshape->shape[0].w = fshape->size;
        fshape->shape[0].h = fshape->size;
        //2 block
        fshape->shape[1].x = fshape->x - fshape->size;
        fshape->shape[1].y = fshape->y;
        fshape->shape[1].w = fshape->size;
        fshape->shape[1].h = fshape->size;
        //3 block
        fshape->shape[2].x = fshape->x;
        fshape->shape[2].y = fshape->y;
        fshape->shape[2].w = fshape->size;
        fshape->shape[2].h = fshape->size;
        //4 block
        fshape->shape[3].x = fshape->x;
        fshape->shape[3].y = fshape->y + fshape->size;
        fshape->shape[3].w = fshape->size;
        fshape->shape[3].h = fshape->size;
    }

    //set color
    int r, g, b, a;
    r = fshape->block_color.r;
    g = fshape->block_color.g;
    b = fshape->block_color.b;
    a = fshape->block_color.a;
    //render filled blocks
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &fshape->shape[0]);
    SDL_RenderFillRect(renderer, &fshape->shape[1]);
    SDL_RenderFillRect(renderer, &fshape->shape[2]);
    SDL_RenderFillRect(renderer, &fshape->shape[3]);
}
