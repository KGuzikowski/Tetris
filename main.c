#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 500
#define HEIGHT 800

int main(int argc, char *argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
}
