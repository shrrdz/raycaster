#include "../def.h"

SDL_Event event;

void I_InputPoll()
{
    const uint8_t *key = SDL_GetKeyboardState(NULL);

    float speed = key[SDL_SCANCODE_LSHIFT] ? PLAYER_SPEED_SPRINT : PLAYER_SPEED;

    vec2 right =
    {
        -player.direction.y,
         player.direction.x
    };

    vec2 delta = { 0.0F, 0.0F };

    if (key[SDL_SCANCODE_W])
    {
        delta.x += player.direction.x;
        delta.y += player.direction.y;
    }

    if (key[SDL_SCANCODE_S])
    {
        delta.x -= player.direction.x;
        delta.y -= player.direction.y;
    }

    if (key[SDL_SCANCODE_A])
    {
        delta.x -= right.x;
        delta.y -= right.y;
    }

    if (key[SDL_SCANCODE_D])
    {
        delta.x += right.x;
        delta.y += right.y;
    }

    P_PlayerTranslate(delta, speed);

    if (key[SDL_SCANCODE_LEFT])
    {
        P_PlayerRotate(-PLAYER_SENSITIVITY * tick_delta);
    }

    if (key[SDL_SCANCODE_RIGHT])
    {
        P_PlayerRotate(PLAYER_SENSITIVITY * tick_delta);
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
                    // action button
                    case SDLK_SPACE:
                        vec2 tile =
                        {
                            player.position.x + player.direction.x,
                            player.position.y + player.direction.y
                        };

                        // open a door
                        if ((map_tiles[(int) tile.x][(int) tile.y] & T_DOOR) && map_doors[(int) tile.x][(int) tile.y]->state == D_CLOSED)
                        {
                            map_doors[(int) tile.x][(int) tile.y]->state = D_OPENING;
                        }
                    break;

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
