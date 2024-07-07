#ifndef __RENDER_H
#define __RENDER_H

#include <SDL2/SDL.h>

void update(void);
void render(void);

struct FontTextures {
  SDL_Texture *font_regular;
  SDL_Texture *font_italic;
  SDL_Texture *font_bold;
};
extern struct FontTextures fontTextures;

void quit_render(void);
void render_init(void);

#endif
