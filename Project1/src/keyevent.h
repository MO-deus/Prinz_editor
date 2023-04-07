
#include <SDL.h>
#pragma once
enum
{
    SDLK_DIVIDE = SDLK_SLASH,
    SDLK_MULTIPLY = SDLK_ASTERISK,
};

// @params : key - keycode for SDL to recognise
// @return : normalized key value
// @desc : turns the given (num/keypad)key to keyboard key
SDL_Keycode normalize_key(SDL_Keycode key);