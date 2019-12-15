#pragma once

#ifndef __VIDEO_H__
#define __VIDEO_H__

typedef struct video_t
{
    int width, height;

    int *color_buffer;
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

#endif // __VIDEO_H__
