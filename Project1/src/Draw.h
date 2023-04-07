
#pragma once

#ifndef DRAW_H
#define DRAW_H

#include "Config.h"
#include "CharacterSet.h"
#include <SDL.h>

void draw_font(Grid* grid, size_t font_index, int at_x, int at_y, SDL_Color color);

void draw_char(Grid* grid, char c, int at_x, int at_y, SDL_Color color);

void draw_text(Grid* grid, char* text, int at_x, int at_y, int space, SDL_Color color);
#endif //  DRAW_H



