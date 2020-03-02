#pragma once

#ifndef __GLYPH_H__
#define __GLYPH_H__

// width and height of the pixel data of each glyph (not the size displayed on screen!)
#define GLYPH_SIZE   40

extern byte **glyphs;

void R_InitGlyphs();

#endif // __GLYPH_H__
