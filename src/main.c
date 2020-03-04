#include "def.h"

int main()
{
    A_ReadFile("arc/all.arc");

    R_InitTextures();
    R_InitSprites();
    R_InitGlyphs();

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

        R_RenderString("hello, world!", video.width >> 5, video.height >> 4, V_AdaptiveScale(15.0F));

        V_Update();
    }

    return 0;
}
