#ifndef __MAIN_H
#define __MAIN_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <sysexits.h>
#include <stdbool.h>
#include <stdio.h>

struct GameState {
};

extern struct GameState state;
extern SDL_Renderer *renderer;

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480


#endif