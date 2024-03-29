
// Configure file for editor

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

// for character set 
#define FONT_PIXELS_UNKNOWN             1
#define FONT_PIXELS_NON_PRINTABLE_CHAR  1
#define FONT_PIXELS_PRINTABLE_CHAR      5
#define FONT_PIXELS_LINE_COUNT          4

// structs for cell and the grid 
struct Cell
{
    // Rect dimensions and color
    SDL_Rect rect;
    SDL_Color rect_color;

    // Border dimensions and color
    SDL_Rect border;
    SDL_Color border_color;
};
typedef struct Cell Cell;

struct Grid
{
    // x, y, width, height
    SDL_Rect rect;

    // Grid background color
    SDL_Color background_color;

    // Grid border thickness and color
    unsigned int border;
    SDL_Color border_color;

    // Number of cells over the x axis
    int x_cells;
    // Number of cells over the y axis
    int y_cells;

    // Cells boder thickness and color
    unsigned int cells_border;
    SDL_Color cells_border_color;

    // Matrix of Cells
    Cell cells[GRID_MAX_X_CELLS][GRID_MAX_Y_CELLS];
};
typedef struct Grid Grid;


#endif // !CONFIG_H
