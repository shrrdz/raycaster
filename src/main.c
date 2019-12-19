#include "def.h"

int main()
{
    A_ReadFile("arc/all.arc");

    P_InitLevel();

    V_Init(800, 600);

    for (;;)
    {
        I_AcceptInput();

        R_Raycast();

        V_Update();
    }

    return 0;
}
