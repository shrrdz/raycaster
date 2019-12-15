#include "def.h"

int main()
{
    A_ReadFile("arc/all.arc");

    byte *palette = A_GetEntry("PALETTE");

    V_Init(800, 600);

    for (;;)
    {
        V_Clear((0xFF << 24) | (palette[2] << 16) | (palette[1] << 8) | palette[0]);

        V_Update();
    }

    return 0;
}
