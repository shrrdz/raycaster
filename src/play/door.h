#pragma once

#ifndef __DOOR_H__
#define __DOOR_H__

typedef struct door_t
{
    int x, y;

    int texture_id;
} door_t;

extern door_t *doors;

void P_InitDoors();

#endif // __DOOR_H__
