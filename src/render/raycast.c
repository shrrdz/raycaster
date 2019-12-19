#include "../def.h"

/*
            -y
            |
            |
            |
 -x --------+-------- +x
            |
            |
            |
            +y
*/

vec2 ray_origin = { 1.5F, 3.5F };

vec2 look_direction = { 1.0F, 0.0F };

vec2 plane;

void R_Raycast()
{
    float half_fov = video.aspect_ratio * 0.5F;

    // calculate the plane vector
    plane.x = -look_direction.y * half_fov;
    plane.y =  look_direction.x * half_fov;

    // cast a ray for each column of the screen width
    for (int x = 0; x < video.width; x++)
    {
        // x in normalized device coordinates (NDC)
        float ndc_x = 2.0F * x / video.width - 1.0F;

        // current position of the ray
        vec2 ray_position =
        {
            floorf(ray_origin.x),
            floorf(ray_origin.y)
        };

        // direction of the ray in world space
        vec2 ray_direction =
        {
            look_direction.x + plane.x * ndc_x,
            look_direction.y + plane.y * ndc_x
        };

        // distance the ray has to travel from one grid boundary to the next grid boundary of the same axis
        // (in case the player is looking straight down the grid line, an arbitrarily big number is used instead)
        vec2 step =
        {
            (ray_direction.x == 0.0F) ? 1e6F : fabsf(1.0F / ray_direction.x),
            (ray_direction.y == 0.0F) ? 1e6F : fabsf(1.0F / ray_direction.y)
        };

        // distance between the ray's origin to the first grid boundary along each axis
        vec2 intercept =
        {
            (ray_direction.x > 0.0F) ? (ray_position.x + 1.0F - ray_origin.x) * step.x : (ray_origin.x - ray_position.x) * step.x,
            (ray_direction.y > 0.0F) ? (ray_position.y + 1.0F - ray_origin.y) * step.y : (ray_origin.y - ray_position.y) * step.y
        };

        // size of the tile step (signed depending on the direction the ray travels)
        vec2 tile_step =
        {
            sign(ray_direction.x),
            sign(ray_direction.y)
        };

        // *perpendicular* distance to the wall (perpendicular in order to avoid fish-eye distortion)
        float distance = 0.0F;

        // cast a ray to each block on the grid using DDA until it hits a wall
        for (;;)
        {
            if (intercept.x < intercept.y) // intersected the x-line of the grid
            {
                // step in x
                intercept.x += step.x;
                ray_position.x += tile_step.x;

                distance = intercept.x - step.x;
            }
            else // intersected the y-line of the grid
            {
                // step in y
                intercept.y += step.y;
                ray_position.y += tile_step.y;

                distance = intercept.y - step.y;
            }

            // the ray has hit a wall
            if (tiles[(int) ray_position.x][(int) ray_position.y] == 1)
            {
                break;
            }
        }

        int wall_height = (int) (video.height / distance);

        // y-coordinate of the starting and the ending point of the wall
        int wall_start = max(0, (video.height - wall_height) >> 1);
        int wall_end = min((video.height + wall_height) >> 1, video.height - 1);

        // render the ceiling
        R_RenderColumn(x, 0, wall_start - 1, COLOR_CEILING);

        // render the floor
        R_RenderColumn(x, wall_end + 1, video.height - 1, COLOR_FLOOR);

        // render the walls
        R_RenderColumn(x, wall_start, wall_end, COLOR_WALL);
    }
}
