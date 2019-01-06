#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

typedef struct{
    SDL_Rect shape[4];
} I_shape;

typedef struct{
    SDL_Rect shape[4];
} L_shape;

typedef struct{
    SDL_Rect shape[4];
} R_shape;

typedef struct{
    SDL_Rect shape[4];
} S_shape;

typedef struct{
    SDL_Rect shape[4];
} T_shape;

void set_bg(SDL_Renderer *renderer);
void set_text(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *title_font, TTF_Font *score_font, TTF_Font *score_num_font, int score);
void set_grid(SDL_Renderer *renderer);

void drawI_shape(SDL_Renderer *renderer, int x, int y);
void drawL_shape(SDL_Renderer *renderer, int x, int y);
void drawR_shape(SDL_Renderer *renderer, int x, int y);
void drawS_shape(SDL_Renderer *renderer, int x, int y);
void drawT_shape(SDL_Renderer *renderer, int x, int y);

#endif // GRAPHIC_H_INCLUDED
