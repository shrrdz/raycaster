#include "def.h"

int main()
{
    A_ReadFile("arc/all.arc");

    V_Init(800, 600);

    for (;;)
    {
        I_AcceptInput();

        V_Clear(video.palette[0]);

        for (int i = 0; i <= (video.width >> 1); i++)
        {
            R_RenderColumn(i, 0, video.height - 1, video.palette[137]);
        }

        V_Update();
    }

    return 0;
}
