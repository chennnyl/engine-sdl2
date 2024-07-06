#ifndef __EVENT_H
#define __EVENT_H

#include "main.h" 

int event_loop(void);

typedef int (*EventCallback)(SDL_Event);

struct EventHandler {
  SDL_EventType type;
  EventCallback callback;
};

#endif
