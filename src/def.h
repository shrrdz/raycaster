#pragma once

#ifndef __DEF_H__
#define __DEF_H__

//-----------------------------------------------------//

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

//-----------------------------------------------------//

typedef unsigned char byte;

//-----------------------------------------------------//

#define MAP_SIZE   8

//-----------------------------------------------------//

#include "archive/arc.h"

#include "interface/input.h"
#include "interface/print.h"

#include "play/level.h"

#include "render/render.h"

#include "video/video.h"

//-----------------------------------------------------//

#endif // __DEF_H__
