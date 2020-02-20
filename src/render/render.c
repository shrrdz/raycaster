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

void R_RenderColumnTextured(int x, int start, int end, int texture_top, int texture_height, float frac_u, const byte *texture)
{
    if (x < 0 || x >= video.width || start < 0 || end >= video.height)
    {
        I_Error("R_RenderColumnTextured(): from %d to %d at x: %d", start, end, x);
    }

    // how far to step through the texture's v-axis per screen pixel
    float texture_step_v = (float) TEXTURE_SIZE / (float) texture_height;

    // u-coordinate of the texture (fixed for the whole screen column)
    int texture_u = clamp(frac_u * TEXTURE_SIZE, 0, TEXTURE_SIZE - 1);

    int index = start * video.width + x;

    for (int y = start; y <= end; y++, index += video.width)
    {
        // v-coordinate of the texture
        int texture_v = clamp((int) ((y - texture_top) * texture_step_v), 0, TEXTURE_SIZE - 1);

        byte palette_index = texture[texture_v * TEXTURE_SIZE + texture_u];

        if (palette_index != PID_TRANSPARENT)
        {
            video.color_buffer[index] = video.palette[palette_index];
        }
    }
}

void R_RenderQuad(int x, int y, int width, int height, int color)
{
    if (width < 0 || x < 0 || x + width >= video.width || height < 0 || y < 0 || y + height >= video.height)
    {
        I_Error("R_RenderQuad(): width: %d height: %d at x: %d y: %d", width, height, x, y);
    }

    for (int c = x; c <= x + width; c++)
    {
        R_RenderColumn(c, y, y + height, color);
    }
}

void R_RenderQuadTextured(int x, int y, int width, int height, const byte *texture)
{
    if (width < 0 || x < 0 || x + width >= video.width || height < 0 || y < 0 || y + height >= video.height)
    {
        I_Error("R_RenderQuadTextured(): width: %d height: %d at x: %d y: %d", width, height, x, y);
    }

    for (int c = x; c <= x + width; c++)
    {
        float frac_u = (float) (c - x) / (float) (width + 1);

        R_RenderColumnTextured(c, y, y + height, y, height, frac_u, texture);
    }
}
