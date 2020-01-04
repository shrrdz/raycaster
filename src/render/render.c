#include "../def.h"

void R_RenderColumn(int x, int start, int end, int color)
{
    if (x < 0 || x >= video.width || start < 0 || end >= video.height)
    {
        I_Error("R_RenderColumn(): from %d to %d at x: %d", start, end, x);
    }

    int index = start * video.width + x;

    for (int y = start; y <= end; y++, index += video.width)
    {
        video.color_buffer[index] = color;
    }
}

void R_RenderColumnTextured(int x, int start, int end, int wall_height, float wall_hit, int side, int texture_id)
{
    if (x < 0 || x >= video.width || start < 0 || end >= video.height)
    {
        I_Error("R_RenderColumnTextured(): from %d to %d at x: %d", start, end, x);
    }

    // how far to step through the texture's v-axis per screen pixel
    float texture_step_v = (float) TEXTURE_SIZE / (float) wall_height;

    // u-coordinate of the texture (fixed for the whole screen column)
    int texture_u = clamp(wall_hit * TEXTURE_SIZE, 0, TEXTURE_SIZE - 1);

    // darker version of each texture is stored right next to the original version
    byte *texture_data = (side == X) ? textures[texture_id] : textures[texture_id + 1];

    int index = start * video.width + x;

    for (int y = start; y <= end; y++, index += video.width)
    {
        // v-coordinate of the texture
        int texture_v = clamp((int) ((y - (video.height >> 1) + (wall_height >> 1)) * texture_step_v), 0, TEXTURE_SIZE - 1);

        byte palette_index = texture_data[texture_v * TEXTURE_SIZE + texture_u];

        video.color_buffer[index] = video.palette[palette_index];
    }
}
