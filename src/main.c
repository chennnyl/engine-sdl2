#include "main.h"
#include "event.h"
#include "render.h"

struct GameState state = {};
struct FontTextures fontTextures = { NULL };
SDL_Renderer *renderer = NULL;

int main() {
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
    SDL_Log("Init error: %s\n", SDL_GetError());
    exit(EX_SOFTWARE);
  }

  SDL_Window *window;
  SDL_CreateWindowAndRenderer(
      SCREEN_WIDTH*SCREEN_SCALE, SCREEN_HEIGHT*SCREEN_SCALE,
      0,
      &window, &renderer
  );
  if(window == NULL) {
    SDL_Log("Window error: %s\n", SDL_GetError());
    exit(EX_SOFTWARE);
  }
  if(renderer == NULL) {
    SDL_Log("Renderer error: %s\n", SDL_GetError());
    exit(EX_SOFTWARE);
  }

  IMG_Init(IMG_INIT_PNG);
  render_init();

  while(true) {
    update();
    if(event_loop() < 0) {
      break;
    }
    render();
  }
  
  quit_render();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
}
