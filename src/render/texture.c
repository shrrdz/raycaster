#include "../def.h"

byte **textures;

void R_InitTextures()
{
    // TODO: include the count of textures in the ARC file instead of hardcoding it here
    int texture_count = 2;

    textures = malloc(texture_count * sizeof(byte *));

    for (int i = 0; i < texture_count; i++)
    {
        textures[i] = malloc(TEXTURE_SIZE * TEXTURE_SIZE * sizeof(byte));
    }

    memcpy(textures[0], A_GetEntry("TEXTURE0"), TEXTURE_SIZE * TEXTURE_SIZE * sizeof(byte));
    memcpy(textures[1], A_GetEntry("TEXTURE1"), TEXTURE_SIZE * TEXTURE_SIZE * sizeof(byte));
}
