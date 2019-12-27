#pragma once

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

// all textures are expected to be 64x64 large
#define TEXTURE_SIZE    64

extern byte **textures;

void R_InitTextures();

#endif // __TEXTURE_H__
