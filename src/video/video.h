#pragma once

#ifndef __VIDEO_H__
#define __VIDEO_H__

typedef struct video_t
{
    int width, height;
    float aspect_ratio;

    int palette[256];
    int *color_buffer;

    float *depth_buffer;
} video_t;

extern video_t video;

/*
    initializes the video with the given width and height
*/
void V_Init(int width, int height);

/*
    updates and displays the contents of the video
*/
void V_Update();

/*
    sets all the pixels' color in the color buffer to the given color
*/
void V_Clear(int color);

/*
    sets a color palette used by the video
*/
void V_SetPalette(const byte *palette);

/*
    scales the input to a size that adapts to different screen sizes
*/
int V_AdaptiveScale(float scale);

#endif // __VIDEO_H__
