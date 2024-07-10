#include "main.h"
#include "render.h"

#define CHARS_PER_ROW 32      // characters in 1 row of font image
#define FONT_WIDTH 6          // width of a glyph
#define FONT_HEIGHT 13        // height of a glyph
#define FONT_OUTER_PADDING 1  // blank space around whole font image
#define FONT_INNER_PADDING 1       // blank space around an individual glyph
static void set_text_color(SDL_Texture *font_tex, char text_code);

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
void typeset(const char *string, enum FontType font, SDL_Rect textbox) {
  typeset_n(string, strlen(string), font, textbox);
}
void typeset_n(const char *string, int n, enum FontType font, SDL_Rect textbox) {
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
  WHITE = '\x1', BLACK = '\x2', RED = '\x3', GREEN = '\x4', BLUE = '\x5'
};

#define TO_RGB(hex) (((hex)>>16) & 0xFF), (((hex)>>8) & 0xFF), ((hex) & 0xFF)

static void set_text_color(SDL_Texture *font_tex, char text_code) {
  switch((enum TextColor)text_code) {
    case BLACK:
      SDL_SetTextureColorMod(font_tex, TO_RGB(0x000000));
      break;
    case RED:
      SDL_SetTextureColorMod(font_tex, TO_RGB(0xFF0000));
      break;
    case BLUE:
      SDL_SetTextureColorMod(font_tex, TO_RGB(0x00FF00));
      break;
    case GREEN:
      SDL_SetTextureColorMod(font_tex, TO_RGB(0x0000FF));
      break;
    default: // white
      SDL_SetTextureColorMod(font_tex, TO_RGB(0xFFFFFF));
  }
}
