
#include "Draw.h"

void set_cell_color(Grid* grid, int x, int y, SDL_Color color)
{
    if (x >= 0 && x <= grid->x_cells && y >= 0 && y <= grid->y_cells)
    {
        grid->cells[x][y].rect_color = color;
    }
}

void draw_font(Grid* f_grid, size_t f_font_index, int at_x, int at_y, SDL_Color color)
{
    for (int x = 0; x < 4 && at_x + x < f_grid->x_cells; ++x)
    {
        const size_t k = f_font_index + x;
        for (int y = 0; y < 6 && at_y + y < f_grid->y_cells; ++y)
        {
            set_cell_color(
                f_grid,
                at_x + x,
                at_y + y,
                (FONT_PIXELS[k] & (1 << y)) ? color : f_grid->background_color
            );
        }
    }
}

void draw_char(Grid* grid, char c, int at_x, int at_y, SDL_Color color)
{
    size_t font_index = FONT_PIXELS_UNKNOWN;

    // 'space' is where the printable ascii char code starts
    // ' ~ ' is where it ends
    if (c >= ' ' && c <= '~')
    { 
        // multiplying by 4 since the element of character set is 4 lines long
        font_index = ((size_t)(c - (char)' ') * (size_t)FONT_PIXELS_LINE_COUNT) + (size_t)FONT_PIXELS_PRINTABLE_CHAR;
    }

    draw_font(grid, font_index, at_x, at_y, color);
}

void draw_text(Grid* grid, char* text, int at_x, int at_y, int space, SDL_Color color)
{
    int cursor_x = at_x;
    int cursor_y = at_y;

    int i = 0;
    while (text[i] && cursor_y < grid->y_cells)
    {
        draw_char(grid, text[i], cursor_x, cursor_y, color);
        cursor_x += FONT_PIXELS_LINE_COUNT + space;
        i++;

        // Word wrap
        if (cursor_x > grid->x_cells - FONT_PIXELS_LINE_COUNT)
        {
            cursor_x = at_x;
            cursor_y += 6 + space;

            // Skip space
            if (text[i] == ' ')
                i++;
        }
    }
}