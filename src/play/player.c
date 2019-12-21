#include "../def.h"

player_t player;

void P_InitPlayer()
{
    player.position.x = 1.5F;
    player.position.y = 3.5F;

    player.direction.x = 1.0F;
    player.direction.y = 0.0F;

    player.plane.x = 0.0F;
    player.plane.y = 0.0F;
}
