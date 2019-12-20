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
