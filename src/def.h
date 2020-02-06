#pragma once

#ifndef __DEF_H__
#define __DEF_H__

//-----------------------------------------------------//

#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

typedef struct ivec2
{
    int x, y;
} ivec2;

//-----------------------------------------------------//

#define MAP_SIZE            8

#define COLOR_FLOOR         video.palette[7]
#define COLOR_CEILING       video.palette[4]

// tile types

#define T_NONE              0
#define T_WALL              (1 << 0)
#define T_DOOR              (1 << 1)
#define T_PUSH              (1 << 2)

// special palette indexes

#define PID_TRANSPARENT     255

//-----------------------------------------------------//

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

#define sign(x) ((x) > 0) - ((x) < 0)

#define clamp(x, lo, hi) (((x) > (hi)) ? (hi) : (((x) < (lo)) ? (lo) : (x)))

#define frac(x) ((x) - floorf(x))

//-----------------------------------------------------//

#include "archive/arc.h"

#include "interface/input.h"
#include "interface/print.h"
#include "interface/tick.h"

#include "play/door.h"
#include "play/level.h"
#include "play/player.h"
#include "play/push.h"

#include "render/raycast.h"
#include "render/render.h"
#include "render/sprite.h"
#include "render/texture.h"

#include "video/video.h"

//-----------------------------------------------------//

#endif // __DEF_H__
