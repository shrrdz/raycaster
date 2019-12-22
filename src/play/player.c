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

void P_PlayerTranslate(vec2 direction, float speed)
{
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);

    if (length > 0.0F)
    {
        // normalize to prevent additional speed upon diagonal input
        direction.x /= length;
        direction.y /= length;

        direction.x *= speed * tick_delta;
        direction.y *= speed * tick_delta;

        player.position.x += direction.x;
        player.position.y += direction.y;
    }
}

void P_PlayerRotate(float radians)
{
    /*
        rotation around the z-axis:

            | cos(θ) -sin(θ)    0 |
            | sin(θ)  cos(θ)    0 |
            |   0       0       1 |
    */

    float sin = sinf(radians);
    float cos = cosf(radians);

    vec2 old_plane = player.plane;
    vec2 old_direction = player.direction;

    player.plane.x = old_plane.x * cos - old_plane.y * sin;
    player.plane.y = old_plane.x * sin + old_plane.y * cos;

    player.direction.x = old_direction.x * cos - old_direction.y * sin;
    player.direction.y = old_direction.x * sin + old_direction.y * cos;
}
