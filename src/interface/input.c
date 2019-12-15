#include "../def.h"

SDL_Event event;

void I_InputPoll()
{
    const uint8_t *key = SDL_GetKeyboardState(NULL);

    if (key[SDL_SCANCODE_SPACE])
    {
        printf("I_InputPoll(): spacebar pressed\n");
    }
}

void I_InputEvent()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                // only handle the initial press
                if (event.key.repeat)
                {
                    break;
                }

                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        SDL_Quit();
                        exit(EXIT_SUCCESS);
                    break;
                }
            break;

            case SDL_QUIT:
                SDL_Quit();
                exit(EXIT_SUCCESS);
            break;
        }
    }
}

void I_AcceptInput()
{
    I_InputPoll();
    I_InputEvent();
}
