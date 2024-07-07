#include "main.h"
#include "render.h"
#include "paths.h"
#include <string.h>

enum FontType {
  REGULAR, BOLD, ITALIC
};

static void typeset(const char *, enum FontType, SDL_Rect);
static void typeset_n(const char *, int, enum FontType, SDL_Rect);
static void set_text_color(SDL_Texture *font_tex, char text_code);

void render(void) {
  static const char *display_string = "Hello, world!\nThis is a\x2 test\x1 of my\nrendering routine";
  static int progress = 0;
  static int frame = 0;
  int FRAMES_PER_PRINT = 2;

  SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255);
  SDL_RenderClear(renderer);

  typeset_n(display_string, progress, REGULAR, (SDL_Rect) {
    240, 256, 128, 128
  });
  typeset_n(display_string, progress, BOLD, (SDL_Rect) {
    368, 256, 128, 128
  });
  typeset_n(display_string, progress, ITALIC, (SDL_Rect) {
    496, 256, 128, 128
  });

  if(progress < strlen(display_string)) {
    if(!(frame++ % FRAMES_PER_PRINT)) progress++;
  }
  //typeset("\x1Hello,\n\x2world!", REGULAR, (SDL_Rect){ 480, 256, 128, 128 });
  //typeset("Hello,\nworld!", REGULAR, (SDL_Rect){ 240, 256, 128, 128 });
  
  SDL_RenderPresent(renderer);
}

void update(void) {

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
  initializeFonts();
}

#define CHARS_PER_ROW 32      // characters in 1 row of font image
#define FONT_WIDTH 6          // width of a glyph
#define FONT_HEIGHT 13        // height of a glyph
#define FONT_OUTER_PADDING 1  // blank space around whole font image
#define FONT_INNER_PADDING 1       // blank space around an individual glyph
static SDL_Rect get_character_bounding_box(char c, enum FontType font) {
  int offset = font == ITALIC ? 31 : 0; // italic font omits first row
  int index = (int)c - offset;
  int row = index / CHARS_PER_ROW;
  int col = index % CHARS_PER_ROW;
  return (SDL_Rect) {
    .x = FONT_OUTER_PADDING + col*(2*FONT_INNER_PADDING + FONT_WIDTH) + FONT_INNER_PADDING,
    .y = FONT_OUTER_PADDING + row*(2*FONT_INNER_PADDING + FONT_HEIGHT) + FONT_INNER_PADDING,
    .w = FONT_WIDTH, .h = FONT_HEIGHT
  };
}
static void typeset(const char *string, enum FontType font, SDL_Rect textbox) {
  typeset_n(string, strlen(string), font, textbox);
}
static void typeset_n(const char *string, int n, enum FontType font, SDL_Rect textbox) {
  SDL_Texture *font_tex;
  switch(font) {
    case ITALIC:
      font_tex = fontTextures.font_italic;
      break;
    case REGULAR:
      font_tex = fontTextures.font_regular;
      break;
    case BOLD:
      font_tex = fontTextures.font_bold;
  }
  unsigned char cr, cg, cb;
  SDL_GetTextureColorMod(font_tex, &cr, &cg, &cb);

  int box_width   = textbox.w / FONT_WIDTH;
  int box_height  = textbox.h / FONT_HEIGHT;
  int max_chars   = box_width*box_height;
  int total_chars = n > max_chars ? max_chars : n;

  SDL_Rect drawRect = textbox;
  drawRect.w = FONT_WIDTH;
  drawRect.h = FONT_HEIGHT;

  int char_count = 0; // some processing should not increase character count
  int line_count = 0;
  for(int c = 0; c < total_chars; c++) {
    // newlines can take us outside of the textbox
    if(drawRect.y >= textbox.y+textbox.h) {
      break;
    }
    // process newline
    if(string[c] == '\n') {
      drawRect.x = textbox.x;
      drawRect.y += FONT_HEIGHT;
      line_count = 0;
      continue;
    } 
    // color codes with \x00 - \x1f
    if(string[c] < ' ') {
      set_text_color(font_tex, string[c]);
      continue;
    }
    SDL_Rect boundingBox = get_character_bounding_box(string[c], font);
    SDL_RenderCopy(renderer, font_tex, &boundingBox, &drawRect);
    if(line_count == box_width) {
      drawRect.x = textbox.x;
      drawRect.y += FONT_HEIGHT;
      line_count = 0;
    } else {
      drawRect.x += FONT_WIDTH;
    }
    char_count++;
    line_count++;
  }
  
  // reset color mod to pre-call
  SDL_SetTextureColorMod(font_tex, cr, cg, cb);
}

enum TextColor {
  WHITE = '\x1', BLACK = '\x2', RED = '\x3', BLUE = '\x4'
};

static void set_text_color(SDL_Texture *font_tex, char text_code) {
  switch((enum TextColor)text_code) {
    case BLACK:
      SDL_SetTextureColorMod(font_tex, 0, 0, 0);
      break;
    case RED:
      SDL_SetTextureColorMod(font_tex, 255, 0, 0);
      break;
    case BLUE:
      SDL_SetTextureColorMod(font_tex, 0, 0, 255);
      break;
    default: // white
      SDL_SetTextureColorMod(font_tex, 255, 255, 255);
  }
}
