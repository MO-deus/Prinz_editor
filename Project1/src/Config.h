
#ifndef CONFIG_H
#define CONFIG_H

#include <SDL.h>

// colors
									// alpha is set to 1
#define _COLOR(RED, GREEN, BLUE)    { RED, GREEN, BLUE, 0xFF }
#define COLOR(RED, GREEN, BLUE)     ((SDL_Color) { RED, GREEN, BLUE, 0xFF })

const SDL_Color NO_COLOR = { 0, 0, 0, 0 };
const SDL_Color COLOR_BLACK = _COLOR(0, 0, 0);
const SDL_Color COLOR_WHITE = _COLOR(0xFF, 0xFF, 0xFF);
const SDL_Color COLOR_GRAY = _COLOR(0x64, 0x64, 0x64);
const SDL_Color COLOR_DARK_GRAY = _COLOR(0x1E, 0x1E, 0x1E);
const SDL_Color COLOR_LIGHT_GRAY = _COLOR(0xC8, 0xC8, 0xC8);
const SDL_Color COLOR_RED = _COLOR(0xF5, 0x3B, 0x56);
const SDL_Color COLOR_GREEN = _COLOR(0x01, 0x9F, 0x13);
const SDL_Color COLOR_BLUE = _COLOR(0x38, 0x95, 0xD3);
const SDL_Color COLOR_YELLOW = _COLOR(0xF7, 0xDC, 0x11);
const SDL_Color COLOR_ORANGE = _COLOR(0xFF, 0x85, 0);
const SDL_Color COLOR_PINK = _COLOR(0xFF, 0, 0xCE);
const SDL_Color COLOR_VIOLET = _COLOR(0x91, 0, 0xFF);

// Define screen dimensions
#define SCREEN_WIDTH        (800)
#define SCREEN_HEIGHT       (600)

// Max grid dimension
#define GRID_MAX_X_CELLS    (66)
#define GRID_MAX_Y_CELLS    (57)	

#define GRID_DEFAULT_MARGIN         (5)
#define GRID_DEFAULT_COLOR          COLOR_WHITE
#define GRID_DEFAULT_BORDER_SIZE    (0)
#define GRID_DEFAULT_BORDER_COLOR   COLOR_BLACK

#define USE_AZERTY_KEYBOARD         0

// Define MAX and MIN macros
#define max(X, Y) (((X) > (Y)) ? (X) : (Y))
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

#endif // !CONFIG_H
