#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

typedef struct player_t
{
    // current position of the player (also the origin of the ray)
    vec2 position;

    // direction the player is currently looking
    vec2 direction;

    // vector of the view plane (always perpendicular to the player's look direction)
    vec2 plane;
} player_t;

extern player_t player;

void P_InitPlayer();

#endif // __PLAYER_H__
