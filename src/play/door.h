#pragma once

#ifndef __DOOR_H__
#define __DOOR_H__

typedef struct door_t
{
    int x, y;

    int texture_id;

    // opening speed
    float speed;

    // 0 = fully closed, 1 = fully open
    float open;

    enum door_state
    {
        D_CLOSED, D_OPENING, D_OPEN
    } state;
} door_t;

extern door_t *doors;
extern door_t *map_doors[MAP_SIZE][MAP_SIZE];

void P_InitDoors();
void P_UpdateDoors();

#endif // __DOOR_H__
