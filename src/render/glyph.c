#include "../def.h"

byte **glyphs;

void R_InitGlyphs()
{
    int first_glyph = A_FindEntry("G_START") + 1;
    int last_glyph = A_FindEntry("G_END") - 1;

    int glyph_count = last_glyph - first_glyph + 1;

    glyphs = malloc(glyph_count * sizeof(byte *));

    int entry_index = first_glyph;

    for (int i = 0; i < glyph_count; i++)
    {
        glyphs[i] = malloc(GLYPH_SIZE * GLYPH_SIZE * sizeof(byte));

        memcpy(glyphs[i], A_GetEntryByIndex(entry_index++), GLYPH_SIZE * GLYPH_SIZE * sizeof(byte));
    }
}
