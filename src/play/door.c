#include "../def.h"

door_t *doors;

void P_InitDoors()
{
    int door_count = A_GetEntrySize("DOORS") / sizeof(door_t);

    doors = malloc(door_count * sizeof(door_t));

    memcpy(doors, A_GetEntry("DOORS"), door_count * sizeof(door_t));

    for (int i = 0; i < door_count; i++)
    {
        door_t *door = &doors[i];

        map_tiles[door->x][door->y] = T_DOOR;
        map_textures[door->x][door->y] = door->texture_id;
    }
}
