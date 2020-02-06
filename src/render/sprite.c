#include "../def.h"

sprite_t *sprites;

int sprite_count;

void R_InitSprites()
{
    sprite_count = A_GetEntrySize("SPRITES") / sizeof(sprite_t);

    sprites = malloc(sprite_count * sizeof(sprite_t));

    memcpy(sprites, A_GetEntry("SPRITES"), sprite_count * sizeof(sprite_t));
}

void R_RenderSprites()
{
    // sort sprites by distance from the player in descending order
    for (int i = 0; i < sprite_count; i++)
    {
        for (int j = 0; j < sprite_count - i - 1; j++)
        {
            sprite_t *first = &sprites[j];
            sprite_t *second = &sprites[j + 1];

            float distance_first = (first->x - player.position.x) * (first->x - player.position.x) + (first->y - player.position.y) * (first->y - player.position.y);
            float distance_second = (second->x - player.position.x) * (second->x - player.position.x) + (second->y - player.position.y) * (second->y - player.position.y);

            if (distance_first < distance_second)
            {
                sprite_t stored = sprites[j];

                sprites[j] = sprites[j + 1];
                sprites[j + 1] = stored;
            }
        }
    }

    /*
        view matrix:

            | plane.x        plane.y     |
            | direction.x    direction.y |
    */

    float inverse_determinant = 1.0F / (player.plane.x * player.direction.y - player.plane.y * player.direction.x);

    for (int i = 0; i < sprite_count; i++)
    {
        sprite_t *sprite = &sprites[i];

        // sprite position relative to the player's view
        vec2 sprite_position_relative =
        {
            (float) sprite->x + 0.5F - player.position.x,
            (float) sprite->y + 0.5F - player.position.y
        };

        /*
            sprite's position transformed into view space:

                V^-1 * sprite_position

            where: V^-1 = 1 / det(V) * adj(V)

        */
        vec2 sprite_position_view_space =
        {
            inverse_determinant * (player.direction.y * sprite_position_relative.x - player.direction.x * sprite_position_relative.y),
            inverse_determinant * (-player.plane.y * sprite_position_relative.x + player.plane.x * sprite_position_relative.y)
        };

        float depth = sprite_position_view_space.y;

        // the sprite is behind or directly on the player's view plane
        if (depth <= 0.0F)
        {
            continue;
        }

        int sprite_width = (int) (video.height / depth);
        int sprite_height = (int) (video.height / depth);

        int sprite_screen_space_x = (int) ((video.width >> 1) * (1 + sprite_position_view_space.x / sprite_position_view_space.y));

        int x_start = max(0, (-sprite_width >> 1) + sprite_screen_space_x);
        int x_end = min((sprite_width >> 1) + sprite_screen_space_x, video.width);

        int y_start = max(0, (-sprite_height >> 1) + (video.height >> 1));
        int y_end = min((sprite_height >> 1) + (video.height >> 1), video.height);

        byte *texture_data = textures[sprite->texture_id];

        for (int x = x_start; x < x_end; x++)
        {
            if (depth > video.depth_buffer[x])
            {
                continue;
            }

            int texture_u = (x - (sprite_screen_space_x - (sprite_width >> 1))) * TEXTURE_SIZE / sprite_width;

            for (int y = y_start; y < y_end; y++)
            {
                int texture_v = (((y << 1) - video.height + sprite_height) * TEXTURE_SIZE) / (sprite_height << 1);

                byte palette_index = texture_data[texture_v * TEXTURE_SIZE + texture_u];

                if (palette_index != PID_TRANSPARENT)
                {
                    video.color_buffer[y * video.width + x] = video.palette[palette_index];
                }
            }
        }
    }
}
