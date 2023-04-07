
#include "keyevent.h"

SDL_Keycode normalize_key(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_KP_0:
        return SDLK_0;
    case SDLK_KP_1:
        return SDLK_1;
    case SDLK_KP_2:
        return SDLK_2;
    case SDLK_KP_3:
        return SDLK_3;
    case SDLK_KP_4:
        return SDLK_4;
    case SDLK_KP_5:
        return SDLK_5;
    case SDLK_KP_6:
        return SDLK_6;
    case SDLK_KP_7:
        return SDLK_7;
    case SDLK_KP_8:
        return SDLK_8;
    case SDLK_KP_9:
        return SDLK_9;
    case SDLK_KP_ENTER:
        return SDLK_RETURN;
    case SDLK_KP_PERIOD:
        return SDLK_PERIOD;
    case SDLK_KP_COMMA:
        return SDLK_COMMA;
    case SDLK_KP_COLON:
        return SDLK_COLON;
    case SDLK_KP_PERCENT:
        return SDLK_PERCENT;

#if USE_AZERTY_KEYBOARD
    case 249:
        return SDLK_PERCENT;
#endif

    case SDLK_KP_PLUS:
        return SDLK_PLUS;
    case SDLK_KP_MINUS:
        return SDLK_MINUS;
    case SDLK_KP_MULTIPLY:
        return SDLK_MULTIPLY;
    case SDLK_KP_DIVIDE:
        return SDLK_DIVIDE;
    case SDLK_KP_EQUALS:
        return SDLK_EQUALS;
    default:
        break;
    }

    return key;
}
