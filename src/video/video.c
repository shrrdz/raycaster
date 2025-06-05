#include "../def.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;

video_t video;

void V_Init(int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("", width, height, 0, &window, &renderer);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);

    SDL_SetRenderVSync(renderer, 1);
    SDL_SetWindowRelativeMouseMode(window, true);

    video.width = width;
    video.height = height;
    video.aspect_ratio = (float) video.width / (float) video.height;

    video.color_buffer = malloc(video.width * video.height * sizeof(int));
    video.depth_buffer = malloc(video.width * sizeof(float));

    V_SetPalette(A_GetEntry("PALETTE"));
}

void V_Update()
{
    SDL_UpdateTexture(texture, NULL, video.color_buffer, video.width * sizeof(int));

    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
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
    for (int i = 0; i < PALETTE_SIZE; i++)
    {
        byte r = palette[i * 3 + 0];
        byte g = palette[i * 3 + 1];
        byte b = palette[i * 3 + 2];

        video.palette[i] = (0xFF << 24) | (b << 16) | (g << 8) | r;
    }
}

int V_AdaptiveScale(float scale)
{
    float reference_width = 320.0F;
    float reference_height = 240.0F;

    float scale_x = (float) video.width / reference_width;
    float scale_y = (float) video.height / reference_height;

    float result = (scale_x < scale_y) ? scale_x : scale_y;

    return (int) roundf(result * scale);
}
