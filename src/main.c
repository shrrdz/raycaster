#include "def.h"

int main()
{
    A_ReadFile("arc/all.arc");

    R_InitTextures();

    P_InitLevel();
    P_InitPlayer();

    V_Init(800, 600);

    for (;;)
    {
        I_AcceptInput();
        I_Tick();

        P_UpdateLevel();

        R_Raycast();

        V_Update();
    }

    return 0;
}
