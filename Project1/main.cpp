﻿
// 1228 - main()

//***************************************************************************************
// IMPORTANT NOTE:
//
//      To start coding, go down in this file to the 'FREE CODING' section.
//      All your code should be written inside the 'draw' function (line 1725).
//      There is also a 'DOCUMENTATION' section just above the 'FREE CODING' section.
//
//      Read the README.md file for more details.
//
//***************************************************************************************

/*The 4x6 font:
 *  - Upper case letters
 *  - Lower case letters
 *  - Exclamation mark
 *  - Period (punctuation)
 
 * The 4x6 font modification/extension:
 * Some lower case letters have been modifed and the remaining font characters are made
 * by "Amine Ben Hassouna" and are distributed under the same license as this file.
 */

 //****************************************************************************************
 // LIBRARY SECTION
 //****************************************************************************************

#include <stdio.h>
#include <stdbool.h>
#include <cstdlib>
#include <time.h>
#include <SDL.h>
#include "src/Config.h"
#include "src/Draw.h"
#include "src/keyevent.h"

// miscllaneous and helper functions
 
bool is_key_ascii(SDL_Keycode key)
{
    return key >= SDLK_SPACE && key <= SDLK_z;
}

bool is_key_letter(SDL_Keycode key)
{
    return key >= SDLK_a && key <= SDLK_z;
}

bool is_key_digit(SDL_Keycode key)
{
    return key >= SDLK_0 && key <= SDLK_9;
}

bool is_key_arithmetic_op(SDL_Keycode key)
{
    return key == SDLK_PLUS
        || key == SDLK_MINUS
        || key == SDLK_DIVIDE
        || key == SDLK_MULTIPLY
        || key == SDLK_PERCENT;
}

char key_to_char(SDL_Keycode key)
{
    key = normalize_key(key);

    if (is_key_letter(key))
    {
        return (char)(key - SDLK_a + 'A');
    }
    else if (key >= SDLK_SPACE && key <= SDLK_BACKQUOTE)
    {
        return (char)key;
    }

    return 0;
}

char key_to_char_lowercase(SDL_Keycode key)
{
    if (is_key_letter(key))
    {
        return (char)key;
    }
    else
    {
        return key_to_char(key);
    }
}


int key_to_int(SDL_Keycode key)
{
    key = normalize_key(key);

    if (is_key_digit(key))
    {
        return (int)(key - SDLK_0);
    }
    else
    {
        return -1;
    }
}

SDL_Keycode digit_to_key(int digit)
{
    return (abs(digit) % 10) + SDLK_0;
}

char digit_to_char(int digit)
{
    return (abs(digit) % 10) + '0';
}

int char_to_digit(const char c)
{
    return c - '0';
}


void set_background_color(SDL_Renderer* renderer, SDL_Color color)
{
    // Initialize renderer color
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Clear screen
    SDL_RenderClear(renderer);
}

int random_int(int min, int max)
{
    return (std::rand() % (max + 1)) + min;
}

bool is_color_equal(SDL_Color color1, SDL_Color color2)
{
    return *((Sint32*)&color1) == *((Sint32*)&color2);
}

void init_cell(Grid* grid, Cell* cell, int i, int j, SDL_Color color, SDL_Color border_color)
{
    // Init rect
    int interspace_width = grid->x_cells * grid->cells_border * 2;
    cell->rect.w = (grid->rect.w - (grid->border * 2) - interspace_width) / grid->x_cells;

    int interspace_heigth = grid->y_cells * grid->cells_border * 2;
    cell->rect.h = (grid->rect.h - (grid->border * 2) - interspace_heigth) / grid->y_cells;

    cell->rect.x = grid->rect.x + grid->border + grid->cells_border
        + (grid->cells_border * 2 + cell->rect.w) * i;
    cell->rect.y = grid->rect.y + grid->border + grid->cells_border
        + (grid->cells_border * 2 + cell->rect.h) * j;

    // Init rectColor
    cell->rect_color = color;

    // Init border
    cell->border.w = cell->rect.w + grid->cells_border * 2;
    cell->border.h = cell->rect.h + grid->cells_border * 2;
    cell->border.x = cell->rect.x - grid->cells_border;
    cell->border.y = cell->rect.y - grid->cells_border;

    // Init borderColor
    cell->border_color = border_color;
}

bool init_grid(Grid* grid)
{
    if (!grid->rect.w || !grid->rect.h || !grid->x_cells || !grid->y_cells)
    {
        fprintf(stderr, "Grid dimensions or number of cells not initialised !\n");
        return false;
    }

    if (grid->x_cells > GRID_MAX_X_CELLS || grid->y_cells > GRID_MAX_Y_CELLS)
    {
        fprintf(stderr, "Grid number of cells (%d,%d) is greater than (%d,%d) !\n",
            grid->x_cells, grid->y_cells,
            GRID_MAX_X_CELLS, GRID_MAX_Y_CELLS);
        return false;
    }

    // Init all cells
    for (int i = 0; i < grid->x_cells; ++i)
    {
        for (int j = 0; j < grid->y_cells; ++j)
        {
            init_cell(grid,
                &(grid->cells[i][j]),
                i, j,
                grid->background_color,
                grid->cells_border_color);
        }
    }

    return true;
}

void render_cell(Cell* cell, SDL_Renderer* renderer)
{
    if (cell->border.x != cell->rect.x) // Cells border thickness different from 0
    {
        // Set renderer color to cell color
        SDL_SetRenderDrawColor(renderer,
            cell->border_color.r,
            cell->border_color.g,
            cell->border_color.b,
            cell->border_color.a);

        // Render filled cell
        SDL_RenderFillRect(renderer, &(cell->border));
    }

    // Set renderer color to cell color
    SDL_SetRenderDrawColor(renderer,
        cell->rect_color.r,
        cell->rect_color.g,
        cell->rect_color.b,
        cell->rect_color.a);

    // Render filled cell
    SDL_RenderFillRect(renderer, &(cell->rect));
}

void render_grid(Grid* grid, SDL_Renderer* renderer)
{
    if (grid->border != 0) // Grid border thickness different from 0
    {
        // Set renderer color to draw the grid border
        SDL_SetRenderDrawColor(renderer,
            grid->border_color.r,
            grid->border_color.g,
            grid->border_color.b,
            grid->border_color.a);

        // Render grid border
        SDL_RenderFillRect(renderer, &(grid->rect));
    }

    // Render all cells
    for (int i = 0; i < grid->x_cells; ++i)
    {
        for (int j = 0; j < grid->y_cells; ++j)
        {
            render_cell(&(grid->cells[i][j]), renderer);
        }
    }
}

int ajust_grid_size(Grid* grid)
{
    if (!grid->rect.w || !grid->rect.h || !grid->x_cells || !grid->y_cells)
    {
        fprintf(stderr, "Grid dimensions or number of cells not initialised !\n");
        return false;
    }

    // Init rect
    int interspace_width = grid->x_cells * grid->cells_border * 2;
    grid->rect.w -= (grid->rect.w - (grid->border * 2) - interspace_width) % grid->x_cells;

    int interspace_heigth = grid->y_cells * grid->cells_border * 2;
    grid->rect.h -= (grid->rect.h - (grid->border * 2) - interspace_heigth) % grid->y_cells;

    return true;
}

void center_grid(Grid* grid, int screen_width, int screen_height)
{
    grid->rect.x = (screen_width - grid->rect.w) / 2;
    grid->rect.y = (screen_height - grid->rect.h) / 2;
}



SDL_Color get_cell_color(Grid* grid, int x, int y)
{
    if (x >= 0 && x <= grid->x_cells && y >= 0 && y <= grid->y_cells)
    {
        return grid->cells[x][y].rect_color;
    }

    return NO_COLOR;
}

void set_cell_border_color(Grid* grid, int x, int y, SDL_Color color)
{
    if (x >= 0 && x <= grid->x_cells && y >= 0 && y <= grid->y_cells)
    {
        grid->cells[x][y].border_color = color;
    }
}

SDL_Color get_cell_border_color(Grid* grid, int x, int y)
{
    if (x >= 0 && x <= grid->x_cells && y >= 0 && y <= grid->y_cells)
    {
        return grid->cells[x][y].border_color;
    }

    return NO_COLOR;
}

void set_grid_color(Grid* grid, SDL_Color color)
{
    grid->background_color = color;

    // Set color of all cells
    for (int x = 0; x < grid->x_cells; ++x)
    {
        for (int y = 0; y < grid->y_cells; ++y)
        {
            grid->cells[x][y].rect_color = color;
        }
    }
}

SDL_Color get_grid_color(Grid* grid)
{
    return grid->background_color;
}

void set_grid_border_color(Grid* grid, SDL_Color color)
{
    grid->border_color = color;
    grid->cells_border_color = color;

    // Set border color of all cells
    for (int x = 0; x < grid->x_cells; ++x)
    {
        for (int y = 0; y < grid->y_cells; ++y)
        {
            grid->cells[x][y].border_color = color;
        }
    }
}

SDL_Color get_grid_border_color(Grid* grid)
{
    return grid->border_color;
}

void draw_key(Grid* grid, SDL_Keycode key, int at_x, int at_y, SDL_Color color)
{
    char c = key_to_char(key);

    draw_char(grid, c, at_x, at_y, color);
}

SDL_Keycode get_key(SDL_Event* event)
{
    if (event->type == SDL_KEYDOWN)
    {
        return event->key.keysym.sym;
    }

    return SDLK_UNKNOWN;
}

bool _is_mouse_over_grid(Grid* grid, int x, int y)
{
    return x >= grid->rect.x && x <= grid->rect.x + grid->rect.w
        && y >= grid->rect.y && y <= grid->rect.y + grid->rect.h;
}

bool is_mouse_over_grid(Grid* grid)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    return _is_mouse_over_grid(grid, x, y);
}

bool is_mouse_clicked(Grid* grid, SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        int x = event->button.x;
        int y = event->button.y;

        return _is_mouse_over_grid(grid, x, y);
    }

    return false;
}

bool is_mouse_moved(Grid* grid, SDL_Event* event)
{
    if (event->type == SDL_MOUSEMOTION)
    {
        int x = event->motion.x;
        int y = event->motion.y;

        return _is_mouse_over_grid(grid, x, y);
    }

    return false;
}

int get_mouse_pos_x(Grid* grid, SDL_Event* event)
{
    if (is_mouse_clicked(grid, event))
    {
        int x = event->button.x;
        return (x - grid->rect.x) / (grid->rect.w / grid->x_cells);
    }
    else if (is_mouse_moved(grid, event))
    {
        int x = event->motion.x;
        return (x - grid->rect.x) / (grid->rect.w / grid->x_cells);
    }
    else
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (_is_mouse_over_grid(grid, x, y))
        {
            return (x - grid->rect.x) / (grid->rect.w / grid->x_cells);
        }
    }

    return -1;
}

int get_mouse_pos_y(Grid* grid, SDL_Event* event)
{
    if (is_mouse_clicked(grid, event))
    {
        int y = event->button.y;
        return (y - grid->rect.y) / (grid->rect.h / grid->y_cells);
    }
    else if (is_mouse_moved(grid, event))
    {
        int y = event->motion.y;
        return (y - grid->rect.y) / (grid->rect.h / grid->y_cells);
    }
    else
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (_is_mouse_over_grid(grid, x, y))
        {
            return (y - grid->rect.y) / (grid->rect.h / grid->y_cells);
        }
    }

    return -1;
}

Uint8 get_mouse_button(Grid* grid, SDL_Event* event)
{
    if (is_mouse_clicked(grid, event))
    {
        return event->button.button;
    }

    return 0;
}

bool start_rendering(SDL_Renderer* renderer, int width, int height);

int main(int argc, char* argv[])
{
    // Unused argc, argv
    (void)argc;
    (void)argv;

    // Initialize the pseudo-random number generator
    srand(time(NULL));

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not be initialized!\n"
            "SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)

    // Disable compositor bypass
    if (!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        fprintf(stderr, "SDL can not disable compositor bypass!\n");
        return 0;
    }

#endif

    // Create window
    SDL_Window* window = SDL_CreateWindow("Prinz - text editor",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        fprintf(stderr, "Window could not be created!\n"
            "SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create renderer
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
        {
            fprintf(stderr, "Renderer could not be created!\n"
                "SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // Start rendering
            start_rendering(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            // Destroy renderer
            SDL_DestroyRenderer(renderer);
        }

        // implemente file save
        // saving the keyboard input (if backspace is pressed, decrement the array by 1)
        // tracing the Grids and saving their cell inputs in the file/array
        
        // Destroy window
        SDL_DestroyWindow(window);

    }

    // Quit SDL
    SDL_Quit();

    return 0;
}

void delay(SDL_Renderer* renderer, Uint32 ms, SDL_Event* event)
{
    event->type = 0;

    for (uint32_t i = 0; i < ms / 10; i++)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            // User requests quit
            if (e.type == SDL_QUIT)
            {
                exit(0);
                break;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                *event = e;
                event->key.keysym.sym = normalize_key(event->key.keysym.sym);
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                *event = e;
            }
            else if (e.type == SDL_MOUSEMOTION)
            {
                *event = e;
            }
        }

        // Update screen
        SDL_RenderPresent(renderer);

        // Wait 1ms
        SDL_Delay(10);
    }
}

bool render_and_delay(SDL_Renderer* renderer, Grid* grid, SDL_Color background_color, Uint32 ms, SDL_Event* event)
{
    // Set white background
    set_background_color(renderer, background_color);

    // Render grid
    render_grid(grid, renderer);

    // Wait
    delay(renderer, ms, event);

    return true;
}

// Global variables
SDL_Renderer* g_renderer = NULL;
Grid g_grid = { 0 };
SDL_Color g_background_color = COLOR_WHITE;
SDL_Event g_event = { 0 };

void draw(int x_cells, int y_cells);

bool start_rendering(SDL_Renderer* renderer, int width, int height)
{
    // Init global renderer
    g_renderer = renderer;

    // Set number of cells
    g_grid.x_cells = GRID_MAX_X_CELLS;
    g_grid.y_cells = GRID_MAX_Y_CELLS;

    // Set grid dimensions
    int margin = GRID_DEFAULT_MARGIN;
    int cell_size = min((width - margin * 2) / g_grid.x_cells,
        (height - margin * 2) / g_grid.y_cells);
    g_grid.rect.w = cell_size * g_grid.x_cells;
    g_grid.rect.h = cell_size * g_grid.y_cells;

    // Set grid backgroud
    g_grid.background_color = GRID_DEFAULT_COLOR;

    // Set grid border thickness and color
    g_grid.border = GRID_DEFAULT_BORDER_SIZE;
    g_grid.border_color = GRID_DEFAULT_BORDER_COLOR;

    // Set cells border thickness and color
    g_grid.cells_border = g_grid.border;
    g_grid.cells_border_color = g_grid.border_color;

    // Ajust size and center
    ajust_grid_size(&g_grid);
    center_grid(&g_grid, width, height);

    if (!init_grid(&g_grid))
    {
        fprintf(stderr, "Grid fail to initialize !\n");
        return false;
    }

    // Set white background
    set_background_color(renderer, g_background_color);
    g_grid.background_color = g_background_color;

    // Render grid
    render_grid(&g_grid, renderer);

    // Update screen
    SDL_RenderPresent(renderer);

    // Draw shapes
    draw(g_grid.x_cells, g_grid.y_cells);

    // Set white background
    set_background_color(renderer, g_background_color);
    g_grid.background_color = g_background_color;

    // Render grid
    render_grid(&g_grid, renderer);

    // Update screen
    SDL_RenderPresent(renderer);

    // Event loop exit flag
    bool quit = false;

    // Event loop
    while (!quit)
    {
        SDL_Event e;

        // Wait indefinitely for the next available event
        SDL_WaitEvent(&e);

        // User requests quit
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }

        SDL_RenderPresent(renderer);
    }

    return true;
}

#define set_background_color(color)                 (g_background_color = color)
#define get_background_color()                      (g_background_color)
#define set_cell_color(x, y, color)                 set_cell_color(&g_grid, x, y, color)
#define get_cell_color(x, y)                        get_cell_color(&g_grid, x, y)
#define set_cell_border_color(x, y, color)          set_cell_border_color(&g_grid, x, y, color)
#define get_cell_border_color(x, y)                 get_cell_border_color(&g_grid, x, y)
#define set_grid_color(color)                       set_grid_color(&g_grid, color)
#define get_grid_color()                            get_grid_color(&g_grid)
#define set_grid_border_color(color)                set_grid_border_color(&g_grid, color)
#define get_grid_border_color()                     get_grid_border_color(&g_grid)
#define delay(ms)                                   render_and_delay(g_renderer, &g_grid, g_background_color, ms, &g_event)
#define get_key()                                   get_key(&g_event)
#define is_mouse_over_grid()                        is_mouse_over_grid(&g_grid)
#define is_mouse_clicked()                          is_mouse_clicked(&g_grid, &g_event)
#define is_mouse_moved()                            is_mouse_moved(&g_grid, &g_event)
#define get_mouse_pos_x()                           get_mouse_pos_x(&g_grid, &g_event)
#define get_mouse_pos_y()                           get_mouse_pos_y(&g_grid, &g_event)
#define get_mouse_button()                          get_mouse_button(&g_grid, &g_event)
#define exit()                                      exit(0)
#define draw_key(key, at_x, at_y, color)            draw_key(&g_grid, key, at_x, at_y, color)
#define draw_char(c, at_x, at_y, color)             draw_char(&g_grid, c, at_x, at_y, color)
#define draw_text(text, at_x, at_y, space, color)   draw_text(&g_grid, text, at_x, at_y, space, color)
#define printf(...)                                 (fprintf (stdout, __VA_ARGS__), fflush(stdout))

//***************************************************************************************
// DOCUMENTATION
//***************************************************************************************
// 
// 
//***************************************************************************************
//
// Available function:
//
//      set_background_color(color)
//          Set the background color to one of the predefined colors
//
//      get_background_color()
//          Get the current background color
//
//      set_cell_color(x, y, color)
//          Set the color of the cell at coordinates (x, y)
//
//      get_cell_color(x, y)
//          Get the current color of the cell at coordinates (x, y)
//
//      set_cell_border_color(x, y, color)  
//          Set the border color of the cell at coordinates (x, y)
//
//      get_cell_border_color(x, y)
//          Get the current border color of the cell at coordinates (x, y)
//
//      set_grid_color(color)
//          Set the grid (all cells) color
//
//      get_grid_color()
//          Get the grid color
//
//      set_grid_border_color(color)
//          Set the grid (and cells) border color
//
//      get_grid_border_color()
//          Get the current grid border color
//
//      delay(ms)
//          Wait a specified number of milliseconds
//
//      get_key()
//          Get the pressed key
//
//      is_mouse_over_grid()
//          Check if the mouse is over the grid.
//
//      is_mouse_clicked()
//          Check if the mouse was clicked (over the grid).
//
//      is_mouse_moved()
//          Check if the mouse was moved (over the grid).
//
//      get_mouse_pos_x()
//          Get the x coordinate of mouse.
//
//      get_mouse_pos_y()
//          Get the y coordinate of mouse.
//
//      get_mouse_button()
//          Get the clicked mouse button (SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT).
//
//      draw_key(key, at_x, at_y, color)
//          Write a key at position (at_x, at_y) with a specific color
//
//      draw_char(c, at_x, at_y, color)
//          Write a character at position (at_x, at_y) with a specific color
//
//      draw_text(text, at_x, at_y, space, color)
//          Write a text at position (at_x, at_y) with a specific color
//          The space parameter represents the spacing between characters
//
//      is_key_ascii(key)
//          Check if a key is an ASCII-based character
//
//      is_key_letter(key)
//          Check if a key is a letter
//
//      is_key_digit(key)
//          Check if a key is a digit
//
//      is_key_arithmetic_op(key)
//          Check if a key is an arithmetic operator (+, -, *, /, %)
//
//      key_to_char(key)
//          Convert a key to a character
//
//      key_to_char_lowercase(key)
//          Convert a key to a lowercase character
//
//      key_to_int(key)
//          Convert a key to a digit (integer)
//
//      digit_to_key(digit)
//          Convert a digit (integer) to a key
//
//      digit_to_char(digit)
//          Convert a digit (integer) to a character
//
//      char_to_digit(c)
//          Convert a character to a digit (integer)
//
//      random_int(min, max)
//          Get a random integer between min and max
//
//      is_color_equal(color1, color2)
//          Check if 'color1' is equal to 'color2' (return a boolean)
//
//      exit()
//          Exit the program
//
// Available colors:
//
//      COLOR_BLACK
//      COLOR_WHITE
//      COLOR_GRAY
//      COLOR_DARK_GRAY
//      COLOR_LIGHT_GRAY
//      COLOR_RED
//      COLOR_GREEN
//      COLOR_BLUE
//      COLOR_YELLOW
//      COLOR_ORANGE
//      COLOR_PINK
//      COLOR_VIOLET
//
// Custom color:
//
//      COLOR( red, green, blue )
//
// Available keys:
//  (Full list at https://wiki.libsdl.org/SDL_Keycode)
//
//      SDLK_RETURN
//      SDLK_SPACE
//      SDLK_BACKSPACE
//      SDLK_ESCAPE
//      SDLK_{character}
//      SDLK_{digit}
//      SDLK_UP
//      SDLK_DOWN
//      SDLK_RIGHT
//      SDLK_LEFT
//      SDLK_EXCLAIM
//      SDLK_PERIOD
//      SDLK_COLON
//      SDLK_EQUALS
//      SDLK_PLUS
//      SDLK_MINUS
//      SDLK_DIVIDE
//      SDLK_MULTIPLY
//      SDLK_PERCENT

//***************************************************************************************
// FREE CODING SECTION
//***************************************************************************************

void draw(int x_cells, int y_cells)
{
    int margin_x = 1;
    int margin_y = 1;

    int cursor_x = margin_x;
    int cursor_y = margin_y;

    int char_spacing = 1;
    int line_spacing = 1;

    bool cursor_shown = false;
    int cursor_timer = 0;

    SDL_Color text_color = COLOR_VIOLET;

    while (true)
    {
        delay(10);

        SDL_Keycode key = get_key();

        if (key != SDLK_UNKNOWN && cursor_shown)
        {
            draw_char(' ', cursor_x, cursor_y, text_color);
        }

        if (key == SDLK_ESCAPE)
        {
            exit();
        }
        else if (is_key_ascii(key))
        {
            char c = key_to_char(key);

            if (cursor_x == margin_x && cursor_y > margin_y && c == ' ')
                continue;

            if (cursor_y > y_cells - 6 - line_spacing)
                continue;

            draw_char(c, cursor_x, cursor_y, text_color);

            if (cursor_x > x_cells - 4 - char_spacing - margin_x)
            {
                // Word wrap
                cursor_x = margin_x;
                cursor_y += 6 + line_spacing;
            }
            else
            {
                cursor_x += 4 + char_spacing;
            }
        }
        else if (key == SDLK_RETURN)
        {
            if (cursor_y <= y_cells - 6)
            {
                cursor_x = margin_x;
                cursor_y += 6 + line_spacing;
            }
        }
        else if (key == SDLK_BACKSPACE)
        {
            if (cursor_x == margin_x)
            {
                if (cursor_y > margin_y)
                {
                    cursor_y -= 6 + line_spacing;
                    cursor_x = (((x_cells - margin_x + line_spacing) / (4 + line_spacing)) - margin_x)
                        * (4 + line_spacing)
                        + margin_x;

                    draw_char(' ', cursor_x, cursor_y, text_color);
                }
            }
            else
            {
                cursor_x -= 4 + char_spacing;
                if (cursor_x < margin_x)
                {
                    cursor_x = margin_x;
                }

                draw_char(' ', cursor_x, cursor_y, text_color);
            }
        }
        else if (key == SDLK_UP)
        {
            if (cursor_y > margin_y)
            {
                cursor_y -= 6 + line_spacing;
            }
        }
        else if (key == SDLK_DOWN)
        {
            if (cursor_y < y_cells - 6 - line_spacing)
            {
                cursor_y += 6 + line_spacing;
            }
        }
        else if (key == SDLK_LEFT)
        {
            if (cursor_x > margin_x)
            {
                cursor_x -= 4 + char_spacing;
            }
        }
        else if (key == SDLK_RIGHT)
        {
            if (cursor_x < x_cells - 4 - char_spacing)
            {
                cursor_x += 4 + char_spacing;
            }
        }

        cursor_timer += 10;
        if (cursor_timer > 300)
        {
            cursor_timer = 0;
            cursor_shown = !cursor_shown;

            if (cursor_y <= y_cells - 6 - line_spacing + 1)
            {
                if (cursor_shown)
                {
                    draw_char('_', cursor_x, cursor_y, text_color);
                }
                else
                {
                    draw_char(' ', cursor_x, cursor_y, text_color);
                }
            }
        }
    }
}