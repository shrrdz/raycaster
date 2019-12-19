#pragma once

#ifndef __DEF_H__
#define __DEF_H__

//-----------------------------------------------------//

#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

//-----------------------------------------------------//

typedef unsigned char byte;

//-----------------------------------------------------//

typedef enum wall_side
{
    X, Y
} wall_side;

//-----------------------------------------------------//

typedef struct vec2
{
    float x, y;
} vec2;

//-----------------------------------------------------//

#define MAP_SIZE        8

#define COLOR_WALL      video.palette[47]
#define COLOR_DARKWALL  video.palette[44]

#define COLOR_FLOOR     video.palette[7]
#define COLOR_CEILING   video.palette[4]

//-----------------------------------------------------//

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

#define sign(x) ((x) > 0) - ((x) < 0)

#define frac(x) ((x) - floorf(x))

//-----------------------------------------------------//

#include "archive/arc.h"

#include "interface/input.h"
#include "interface/print.h"

#include "play/level.h"

#include "render/raycast.h"
#include "render/render.h"

#include "video/video.h"

//-----------------------------------------------------//

#endif // __DEF_H__
