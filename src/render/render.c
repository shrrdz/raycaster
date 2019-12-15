#include "../def.h"

void R_RenderColumn(int x, int start, int end, int color)
{
    for (int y = start; y <= end; y++)
    {
        video.color_buffer[y * video.width + x] = color;
    }
}
