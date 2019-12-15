#include "../def.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;

video_t video;

void V_Init(int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_HIDDEN, &window, &renderer);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);

    SDL_RenderSetVSync(renderer, 1);

    video.width = width;
    video.height = height;

    video.color_buffer = malloc(video.width * video.height * sizeof(int));

    V_SetPalette(A_GetEntry("PALETTE"));
}

void V_Update()
{
    SDL_UpdateTexture(texture, NULL, video.color_buffer, video.width * sizeof(int));

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_ShowWindow(window);
}

void V_Clear(int color)
{
    for (int i = 0; i < video.width * video.height; i++)
    {
        video.color_buffer[i] = color;
    }
}

void V_SetPalette(const byte *palette)
{
    for (int i = 0; i < 256; i++)
    {
        byte r = palette[i * 3 + 0];
        byte g = palette[i * 3 + 1];
        byte b = palette[i * 3 + 2];

        video.palette[i] = (0xFF << 24) | (b << 16) | (g << 8) | r;
    }
}
