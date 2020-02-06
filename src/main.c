#include "def.h"

int main()
{
    A_ReadFile("arc/all.arc");

    R_InitTextures();
    R_InitSprites();

    P_InitLevel();
    P_InitPlayer();

    V_Init(800, 600);

    for (;;)
    {
        I_AcceptInput();
        I_Tick();

        P_UpdateLevel();

        R_Raycast();

        R_RenderSprites();

        V_Update();
    }

    return 0;
}
