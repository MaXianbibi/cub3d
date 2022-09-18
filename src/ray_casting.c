/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 02:37:39 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/18 11:12:05 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int mapHasWallAt(t_mlx *game , float x, float y) {
    if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT) {
        return 1;
    }
    int mapGridIndexX = (int)(x / 64);
    int mapGridIndexY = (int)(y / 64);
	if (game->map.map[mapGridIndexY][mapGridIndexX] != '0')
		return (1);
    return (0);
}


void draw_fov(t_mlx *game)
{
	float cangle = game->player.rotation_angle;
	float j = cangle + FOV_ANGLE;

	while (cangle < j)
	{
		// draw_line(game, cangle - (FOV_ANGLE / 2));
		dda(game, cangle - (FOV_ANGLE / 2));
		cangle += FOV_ANGLE / NUM_RAY;
	}
}

void draw_line(t_mlx *game, float angle)
{
	// int i = 0;
	float px = game->player.x;
	float py = game->player.y;

	while (game->map.map[(int)(py / 64)][(int)(px / 64)] != '1')
	{
		my_mlx_pixel_put(&game->img, px, py, GRN);	
		px += cos(angle);
		py -= sin(angle);
		
		
	}
}

void draw_line_dda(t_mlx *game, float ax, float ay, float angle)
{
	float px = game->player.x;
	float py = game->player.y;
	
	int i = ay - py;
	int k = ax - px;
	int j = 0;
	while (j < sqrt((i * i) + (k * k)))
	{
		my_mlx_pixel_put(&game->img, px, py, GRN);	
		px += cos(angle);
		py -= sin(angle);
		j++;
		
	}	
}

void dda(t_mlx *game, float angle)
{
	angle = normalize_angle(angle);

	(void)game;
	float side_delta_x;
	float side_delta_y;
	float xstep;
	float ystep;
	
	// find side_delta_X
	int is_facing_down = angle > 0 && angle < PI;
	side_delta_y = floor(game->player.y / 64) * 64;
	if (!is_facing_down)
		side_delta_y += 64;
	side_delta_x = game->player.x + (side_delta_y - game->player.y) / tan(angle);
	

	int is_facing_right = angle < 0.5 * PI || angle > 1.5 * PI;
	

	ystep = 64;
	if (is_facing_down)
		ystep *= -1;

	xstep = 64 / tan(angle);
	if (is_facing_right && xstep > 0)
		xstep *= -1;
	if (!is_facing_right && xstep < 0)
		xstep *= -1;
		
	
		
	float next_horz_touch_x = side_delta_x;
	float next_horz_touch_y = side_delta_y;
	
	while (side_delta_x >= 0 && side_delta_y <= WIDTH && side_delta_y >= 0 && side_delta_y <= HEIGHT)
	{		
		float x_to_check = next_horz_touch_x;
		float y_to_check = next_horz_touch_y;
		if (!is_facing_down)
			y_to_check -= 1;

		if(mapHasWallAt(game, x_to_check, y_to_check))
			break;
		else
		{
			next_horz_touch_x += xstep;
			next_horz_touch_y += ystep;
		}
		
		draw_line_dda(game, x_to_check, y_to_check, angle);
		
	}
	// my_mlx_pixel_put(&game->img, horz_wall_hity, horz_wall_hity, RED);


}