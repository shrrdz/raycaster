#include "def.h"

int main()
{
    A_ReadFile("arc/all.arc");

    unsigned char palette[768];

    A_ReadEntry(0, palette);

    for (int i = 0; i < 768; i += 3)
    {
        printf("%u %u %u\n", palette[i], palette[i + 1], palette[i + 2]);
    }

    return 0;
}
