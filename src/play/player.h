#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#define PLAYER_SENSITIVITY      2.0F

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

void P_PlayerRotate(float radians);

#endif // __PLAYER_H__
