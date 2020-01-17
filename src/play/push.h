#pragma once

#ifndef __PUSH_H__
#define __PUSH_H__

typedef struct pushable_t
{
    int x, y;

    int texture_id;

    // how many tiles the pushable is pushed
    int distance;

    // pushing speed
    float speed;

    // 0 = pushed, 1 = not pushed (per tile)
    float open;

    enum pushable_state
    {
        P_CLOSED, P_OPENING, P_OPEN
    } state;

    enum pushable_direction
    {
        P_NORTH, P_SOUTH, P_EAST, P_WEST
    } direction;
} pushable_t;

extern pushable_t *pushables;
extern pushable_t *map_pushables[MAP_SIZE][MAP_SIZE];

void P_InitPushables();
void P_UpdatePushables();

#endif // __PUSH_H__
