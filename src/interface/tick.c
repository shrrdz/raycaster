#include "../def.h"

float tick_delta = 0.0F;
float tick_previous = 0.0F;

void I_Tick()
{
    int wait = TARGET_TICK - (SDL_GetTicks() - tick_previous);

    if (wait > 0 && wait <= TARGET_TICK)
    {
        SDL_Delay(wait);
    }

    unsigned now = SDL_GetTicks();

    tick_delta = (now - tick_previous) / 1000.0F;
    tick_previous = now;
}
