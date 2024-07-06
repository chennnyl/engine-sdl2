#include "event.h" 

static int keypress_handler(SDL_Event);
static int quit_handler(SDL_Event);

struct EventHandler handlers[] = {
  {
    .type = SDL_QUIT,
    .callback = quit_handler
  },
  {
    .type = SDL_KEYDOWN,
    .callback = keypress_handler
  }
};

SDL_Event event;

int event_loop(void) {
  static int num_handlers = sizeof(handlers)/sizeof(struct EventHandler);
  while(SDL_PollEvent(&event)) {
    for(struct EventHandler *handler = handlers;
        handler < handlers + num_handlers;
        handler++
    ) {
      if(handler->type == event.type) {
        if(handler->callback(event) < 0) {
          return -1;
        }
      }
    }
  }
  return 0;
}

static int quit_handler(SDL_Event event) {
  return -1;
}

static int keypress_handler(SDL_Event event) {
  switch(event.key.keysym.sym) {
    case SDLK_ESCAPE:
      return -1;
    default:
  }
  return 0;
}
