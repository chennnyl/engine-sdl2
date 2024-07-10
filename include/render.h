#ifndef __RENDER_H
#define __RENDER_H

#include <SDL2/SDL.h>

// Loop functions
void update(void);
void render(void);

// Setup and teardown
void quit_render(void);
void render_init(void);

// Font rendering
struct FontTextures {
  SDL_Texture *font_regular;
  SDL_Texture *font_italic;
  SDL_Texture *font_bold;
};
extern struct FontTextures fontTextures;

enum FontType {
  REGULAR, BOLD, ITALIC
};
void typeset(const char *, enum FontType, SDL_Rect);
void typeset_n(const char *, int, enum FontType, SDL_Rect);

#endif
