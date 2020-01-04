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

void R_Raycast()
{
    float half_fov = video.aspect_ratio * 0.5F;

    // calculate the plane vector
    player.plane.x = -player.direction.y * half_fov;
    player.plane.y =  player.direction.x * half_fov;

    // cast a ray for each column of the screen width
    for (int x = 0; x < video.width; x++)
    {
        // x in normalized device coordinates (NDC)
        float ndc_x = 2.0F * x / video.width - 1.0F;

        // current position of the ray
        vec2 ray_position =
        {
            floorf(player.position.x),
            floorf(player.position.y)
        };

        // direction of the ray in world space
        vec2 ray_direction =
        {
            player.direction.x + player.plane.x * ndc_x,
            player.direction.y + player.plane.y * ndc_x
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
            (ray_direction.x > 0.0F) ? (ray_position.x + 1.0F - player.position.x) * step.x : (player.position.x - ray_position.x) * step.x,
            (ray_direction.y > 0.0F) ? (ray_position.y + 1.0F - player.position.y) * step.y : (player.position.y - ray_position.y) * step.y
        };

        // size of the tile step (signed depending on the direction the ray travels)
        vec2 tile_step =
        {
            sign(ray_direction.x),
            sign(ray_direction.y)
        };

        // *perpendicular* distance to the wall (perpendicular in order to avoid fish-eye distortion)
        float distance = 0.0F;

        // exact point where the ray hits the wall
        float hit = 0.0F;

        // side of the wall hit by the ray
        wall_side side = X;

        // cast a ray to each block on the grid using DDA until it hits a wall
        for (;;)
        {
            if (intercept.x < intercept.y) // intersected the x-line of the grid
            {
                side = X;

                // step in x
                intercept.x += step.x;
                ray_position.x += tile_step.x;

                distance = intercept.x - step.x;
                hit = player.position.y + ray_direction.y * distance;
            }
            else // intersected the y-line of the grid
            {
                side = Y;

                // step in y
                intercept.y += step.y;
                ray_position.y += tile_step.y;

                distance = intercept.y - step.y;
                hit = player.position.x + ray_direction.x * distance;
            }

            // the ray has hit a wall
            if (map_tiles[(int) ray_position.x][(int) ray_position.y] == 1)
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
        R_RenderColumnTextured(x, wall_start, wall_end, wall_height, frac(hit), side, map_textures[(int) ray_position.x][(int) ray_position.y]);
    }
}
