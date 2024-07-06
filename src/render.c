#include "main.h"
#include "render.h"

void render(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // SDL_SetRenderDrawColor(renderer, draw color);
  SDL_RenderPresent(renderer);
}

void update(void) {

}
