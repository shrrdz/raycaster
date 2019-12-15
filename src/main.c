#include "def.h"

int main()
{
    A_ReadFile("arc/all.arc");

    V_Init(800, 600);

    for (;;)
    {
        V_Clear(video.palette[0]);

        V_Update();
    }

    return 0;
}
