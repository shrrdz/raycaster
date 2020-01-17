#include "../def.h"

pushable_t *pushables;
pushable_t *map_pushables[MAP_SIZE][MAP_SIZE];

int pushable_count;

void P_InitPushables()
{
    pushable_count = A_GetEntrySize("PUSHABLS") / sizeof(pushable_t);

    pushables = malloc(pushable_count * sizeof(pushable_t));

    memcpy(pushables, A_GetEntry("PUSHABLS"), pushable_count * sizeof(pushable_t));

    for (int i = 0; i < pushable_count; i++)
    {
        pushable_t *pushable = &pushables[i];

        map_pushables[pushable->x][pushable->y] = pushable;

        map_tiles[pushable->x][pushable->y] = T_PUSH;
        map_textures[pushable->x][pushable->y] = pushable->texture_id;
    }
}

void P_UpdatePushables()
{
    for (int i = 0; i < pushable_count; i++)
    {
        pushable_t *pushable = &pushables[i];

        if (pushable->state != P_OPENING)
        {
            continue;
        }

        pushable->open -= pushable->speed * tick_delta;

        if (pushable->open <= 0.0F)
        {
            ivec2 delta = { 0, 0 };

            switch (pushable->direction)
            {
                case P_NORTH: delta.y = -1; break;
                case P_SOUTH: delta.y =  1; break;
                case P_EAST:  delta.x =  1; break;
                case P_WEST:  delta.x = -1; break;
            }

            map_pushables[pushable->x][pushable->y] = NULL;

            map_tiles[pushable->x][pushable->y] = T_NONE;
            map_textures[pushable->x][pushable->y] = 0;

            pushable->x += delta.x;
            pushable->y += delta.y;

            map_pushables[pushable->x][pushable->y] = pushable;

            map_tiles[pushable->x][pushable->y] = T_PUSH;
            map_textures[pushable->x][pushable->y] = map_pushables[pushable->x][pushable->y]->texture_id;

            pushable->open = 1.0F;

            if (--pushable->distance == 0)
            {
                pushable->state = P_OPEN;
            }
        }
    }
}
