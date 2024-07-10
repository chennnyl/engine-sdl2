#include "main.h"
#include "render.h"
#include "paths.h"
#include <string.h>

static const int FRAMES_PER_PRINT = 2;
static int progress = 0;
static int frame = 0;
static const char *display_string = "Hello, world!\n\x2This\x3 is\x4 a\x5 test\x1 of my\nrendering routine";

void render(void) {

  SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255);
  SDL_RenderClear(renderer);

  typeset_n(display_string, progress, REGULAR, (SDL_Rect) {
    64, 64, 128, 128
  });
  typeset_n(display_string, progress, BOLD, (SDL_Rect) {
    64, 128, 128, 128
  });
  typeset_n(display_string, progress, ITALIC, (SDL_Rect) {
    64, 196, 128, 128
  });

  SDL_RenderPresent(renderer);
}

void update(void) {
  if(progress < strlen(display_string)) {
    if(!(frame++ % FRAMES_PER_PRINT)) progress++;
  }
}

void quit_render(void) {
  SDL_DestroyTexture(fontTextures.font_regular);
  SDL_DestroyTexture(fontTextures.font_italic);
  SDL_DestroyTexture(fontTextures.font_bold);
}

static SDL_Texture *load_with_white_color_key(const char *path) {

  SDL_Surface *surf = NULL;
  SDL_Texture *tex  = NULL;

  surf = IMG_Load(path);
  SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0, 0, 0));

  tex = SDL_CreateTextureFromSurface(renderer, surf);
  SDL_FreeSurface(surf);

  return tex;
}
static void initializeFonts(void) {
  struct FontTextures out = { NULL };

  out.font_regular  = load_with_white_color_key(PATH_FONTS "6x13.png"); 
  out.font_bold     = load_with_white_color_key(PATH_FONTS "6x13B.png"); 
  out.font_italic   = load_with_white_color_key(PATH_FONTS "6x13O.png");
  fontTextures = out;
}

void render_init(void) {
  SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
  initializeFonts();
}


