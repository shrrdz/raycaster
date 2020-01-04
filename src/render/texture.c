#include "../def.h"

byte **textures;

void R_InitTextures()
{
    int first_texture = A_FindEntry("T_START") + 1;
    int last_texture = A_FindEntry("T_END") - 1;

    int texture_count = last_texture - first_texture + 1;

    textures = malloc(texture_count * sizeof(byte *));

    int entry_index = first_texture;

    for (int i = 0; i < texture_count; i++)
    {
        textures[i] = malloc(TEXTURE_SIZE * TEXTURE_SIZE * sizeof(byte));

        memcpy(textures[i], A_GetEntryByIndex(entry_index++), TEXTURE_SIZE * TEXTURE_SIZE * sizeof(byte));
    }
}
