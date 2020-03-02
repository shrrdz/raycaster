#pragma once

#ifndef __RENDER_H__
#define __RENDER_H__

void R_RenderColumn(int x, int start, int end, int color);
void R_RenderColumnTextured(int x, int start, int end, int texture_top, int texture_height, float frac_u, const byte *texture, int texture_size);

void R_RenderQuad(int x, int y, int width, int height, int color);
void R_RenderQuadTextured(int x, int y, int width, int height, const byte *texture, int texture_size);

/*
    renders a single character on the screen
*/
void R_RenderChar(char glyph, int x, int y, int size);

/*
    renders a string of characters on the screen
*/
void R_RenderString(const char *string, int x, int y, int size);

#endif // __R_RENDER_H__
