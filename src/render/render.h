#pragma once

#ifndef __RENDER_H__
#define __RENDER_H__

void R_RenderColumn(int x, int start, int end, int color);
void R_RenderColumnTextured(int x, int start, int end, int wall_height, float wall_hit, int side, int texture_id);

#endif // __R_RENDER_H__
