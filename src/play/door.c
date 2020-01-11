#include "../def.h"

door_t *doors;
door_t *map_doors[MAP_SIZE][MAP_SIZE];

int door_count;

void P_InitDoors()
{
    door_count = A_GetEntrySize("DOORS") / sizeof(door_t);

    doors = malloc(door_count * sizeof(door_t));

    memcpy(doors, A_GetEntry("DOORS"), door_count * sizeof(door_t));

    for (int i = 0; i < door_count; i++)
    {
        door_t *door = &doors[i];

        map_doors[door->x][door->y] = door;

        map_tiles[door->x][door->y] = T_DOOR;
        map_textures[door->x][door->y] = door->texture_id;
    }
}

void P_UpdateDoors()
{
    for (int i = 0; i < door_count; i++)
    {
        door_t *door = &doors[i];

        switch (door->state)
        {
            case D_CLOSED:
                door->open = 0.0F;
                door->ticker = door->hold;
            break;

            case D_OPENING:
                door->open += door->speed * tick_delta;

                if (door->open >= 1.0F)
                {
                    door->state = D_OPEN;
                }
            break;

            case D_OPEN:
                door->open = 1.0F;

                if (door->ticker >= 0.0F)
                {
                    door->ticker -= tick_delta;
                }

                if (door->ticker <= 0.0F && door->hold >= 0.0F)
                {
                    door->state = D_CLOSING;
                }
            break;

            case D_CLOSING:
                door->open -= door->speed * tick_delta;

                if (door->open <= 0.0F)
                {
                    door->state = D_CLOSED;
                }
            break;
        }
    }
}
