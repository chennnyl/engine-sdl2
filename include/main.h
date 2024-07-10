#ifndef __MAIN_H
#define __MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <sysexits.h>
#include <stdbool.h>
#include <stdio.h>

struct GameState {
};

extern struct GameState state;
extern SDL_Renderer *renderer;

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240
#define SCREEN_SCALE  2

#endif
