#include "../def.h"

byte map_tiles[MAP_SIZE][MAP_SIZE];
byte map_textures[MAP_SIZE][MAP_SIZE];

void P_InitLevel()
{
    memcpy(map_tiles, A_GetEntry("TILEMAP"), MAP_SIZE * MAP_SIZE * sizeof(byte));
    memcpy(map_textures, A_GetEntry("TEXTMAP"), MAP_SIZE * MAP_SIZE * sizeof(byte));

    P_InitDoors();
    P_InitPushables();
}

void P_UpdateLevel()
{
    P_UpdateDoors();
    P_UpdatePushables();
}
