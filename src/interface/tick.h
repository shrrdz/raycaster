#pragma once

#ifndef __TICK_H__
#define __TICK_H__

#define TARGET_FPS      60.0F
#define TARGET_TICK     1000.0F / TARGET_FPS

// time elapsed between the last two "end of frame" timestamps in seconds
// (i.e. how long the last frame took to render)
extern float tick_delta;

void I_Tick();

#endif // __TICK_H__
