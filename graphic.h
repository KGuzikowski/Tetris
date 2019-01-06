#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

void set_bg(SDL_Renderer *renderer);

void set_text(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *title_font, TTF_Font *score_font);

#endif // GRAPHIC_H_INCLUDED
