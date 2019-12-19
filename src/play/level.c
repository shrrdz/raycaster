#include "../def.h"

byte tiles[MAP_SIZE][MAP_SIZE];

void P_InitLevel()
{
    memcpy(tiles, A_GetEntry("MAP"), MAP_SIZE * MAP_SIZE * sizeof(byte));

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            printf("%d ", tiles[x][y]);
        }

        printf("\n");
    }
}
