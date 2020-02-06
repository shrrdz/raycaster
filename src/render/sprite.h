#pragma once

#ifndef __SPRITE_H__
#define __SPRITE_H__

typedef struct sprite_t
{
    int x, y;

    int texture_id;
} sprite_t;

extern sprite_t *sprites;

extern int sprite_count;

void R_InitSprites();
void R_RenderSprites();

#endif // __SPRITE_H__
