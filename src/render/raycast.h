#pragma once

#ifndef __RAYCAST_H__
#define __RAYCAST_H__

// the ray's origin (current position of the player)
extern vec2 ray_origin;

// direction the player is currently looking
extern vec2 look_direction;

// vector of the view plane (always perpendicular to the player's look direction)
extern vec2 plane;

/*
    casts a ray for each column of the screen width
*/
void R_Raycast();

#endif // __RAYCAST_H__
