/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 02:37:39 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/21 00:25:08 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int mapHasWallAt(t_mlx *game , int x, int y) {
    if (x < 0 || x > (WIDTH / 64) - 1 || y < 0 || y > (HEIGHT / 64) - 1) {
        return 1;
    }
	printf("%d %d \n", y, x);
	if (game->map.map[y][x] != '0')
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
		dda_v2(game, cangle - (FOV_ANGLE / 2));
		// dda(game, cangle - (FOV_ANGLE / 2));
		cangle += FOV_ANGLE / NUM_RAY;
	}
	
}

// void draw_line(t_mlx *game, float angle)
// {
// 	// int i = 0;
// 	float px = game->player.x;
// 	float py = game->player.y;

// 	while (game->map.map[(int)(py / 64)][(int)(px / 64)] != '1')
// 	{
// 		my_mlx_pixel_put(&game->img, px, py, GRN);	
// 		px += cos(angle);
// 		py -= sin(angle);
		
		
// 	}
// }

void draw_line_dda(t_mlx *game, float ax, float ay, float angle)
{
	float px = game->player.x;
	float py = game->player.y;
	
	int i = ay - py;
	int k = ax - px;
	int j = 0;
	// printf("%f\n", ay);

	while (j < sqrt((i * i) + (k * k)))
	{
		my_mlx_pixel_put(&game->img, px, py, GRN);	
		px += cos(angle);
		py -= sin(angle);
		j++;
		
	}	
}

// void dda(t_mlx *game, float angle)
// {
// 	angle = normalize_angle(angle);

// 	(void)game;
// 	float side_delta_x;
// 	float side_delta_y;
// 	float xstep;
// 	float ystep;
	
// 	// find side_delta_X
// 	int is_facing_down = angle > 0 && angle < PI;
// 	side_delta_y = floor(game->player.y / 64) * 64;
// 	if (!is_facing_down)
// 		side_delta_y += 64;
// 	side_delta_x = game->player.x + (side_delta_y - game->player.y) / tan(angle);
	

// 	int is_facing_right = angle < 0.5 * PI || angle > 1.5 * PI;
	

// 	ystep = 64;
// 	if (is_facing_down)
// 		ystep *= -1;

// 	xstep = 64 / tan(angle);
// 	if (is_facing_right && xstep > 0)
// 		xstep *= -1;
// 	if (!is_facing_right && xstep < 0)
// 		xstep *= -1;
		
	
		
// 	float next_horz_touch_x = side_delta_x;
// 	float next_horz_touch_y = side_delta_y;
	
// 	while (side_delta_x >= 0 && side_delta_y <= WIDTH && side_delta_y >= 0 && side_delta_y <= HEIGHT)
// 	{		
// 		float x_to_check = next_horz_touch_x;
// 		float y_to_check = next_horz_touch_y;
// 		if (!is_facing_down)
// 			y_to_check -= 1;

// 		if(mapHasWallAt(game, x_to_check, y_to_check))
// 			break;
// 		else
// 		{
// 			next_horz_touch_x += xstep;
// 			next_horz_touch_y += ystep;
// 		}
		
// 		draw_line_dda(game, x_to_check, y_to_check, angle);
		
// 	}
// 	// my_mlx_pixel_put(&game->img, horz_wall_hity, horz_wall_hity, RED);


// }


t_ray dda_h(t_mlx *game, float angle)
{
	float ra = 0;
	float ry = 0;
	float rx = 0;
	float yo = 0;
	float xo = 0;
	int mx = 0;
	int my = 0;
	float aTan = -1/tan(angle);
	t_ray ray;

	ra = normalize_angle(angle);
	if (ra < PI)
	{
		ry = (((int)game->player.y >> 6) << 6) - 0.0001;
		rx = game->player.x -((game->player.y - ry) * aTan) ;		
		yo = -64;
		xo = (yo * aTan);
	}
	else if (ra > PI)
	{
		ry = (((int)game->player.y >> 6) << 6) + 64;
		rx = game->player.x - ((game->player.y - ry) * aTan); // 
		yo = 64;
		xo = yo * aTan;
	}
	else if (ra == 0 || ra == PI)
	{
		rx = game->player.x;
		ry = game->player.y;
	}
	while (rx >= 0 && rx <= WIDTH && ry >= 0 && ry <= HEIGHT)
	{
		mx = (int)(rx) >> 6;
		my = ((int)(ry) >> 6);	
		if (game->map.map[my][mx] != '0')
			break;
		rx += xo;
		ry += yo;
	}
	
	ray.side_delta_x = rx;
	ray.side_delta_y = ry;
	return (ray);
}

t_ray dda_v(t_mlx *game, float angle)
{
	float ra = 0;
	float ry = 0;
	float rx = 0;
	float yo = 0;
	float xo = 0;
	int mx = 0;
	int my = 0;
	float nTan = -tan(angle);

	t_ray ray;

	ra = normalize_angle(angle);
	if (ra > QUART_PI && ra < QUART3_PI)
	{
		rx = (((int)game->player.x >> 6) << 6) - 0.0001;
		ry =  game->player.y - ((game->player.x - rx) * nTan) ;		
		xo = -64;
		yo = (xo * nTan);
	}
	else if (ra < QUART_PI || ra > QUART3_PI)
	{
		rx = (((int)game->player.x >> 6) << 6) + 64;
		ry = game->player.y - ((game->player.x - rx) * nTan) ;
		xo = 64;
		yo = xo * nTan;
	}
	else if (ra == QUART_PI || ra == QUART3_PI)
	{
		rx = game->player.x;
		ry = game->player.y;
	}
	while ((rx >= 0 && rx <= WIDTH && ry >= 0 && ry <= HEIGHT))
	{
		mx = (int)(rx) >> 6;
		my = ((int)(ry) >> 6);
		
		if (mapHasWallAt(game, mx, my))
			break;
		rx += xo;
		ry += yo;
	}
	ray.side_delta_x = rx;
	ray.side_delta_y = ry;
	return (ray);
}


float dda_v2(t_mlx *game, float angle)
{
	// int r, mx, my, mp, dof;
	// float rx, ry, ra, xo, yo;
	
	// r = 0;
	// mx = 0;
	// mp = 0;
	// dof = 0;
	// rx = 0;
	// ry = 0;
	// ra = 0;
	// xo = 0;
	// yo = 0;
	// my = 0;
	// dof = 0;
	// ra = normalize_angle(angle);


	t_ray	ray_h = dda_h(game, angle);
	t_ray	ray_v = dda_v(game, angle);
	
	float	ray_h_d = sqrt(((ray_h.side_delta_x - game->player.x) * (ray_h.side_delta_x - game->player.x)) + ((ray_h.side_delta_y - game->player.y) * (ray_h.side_delta_y - game->player.y)));
	float	ray_v_d = sqrt(((ray_v.side_delta_x - game->player.x) * (ray_v.side_delta_x - game->player.x)) + ((ray_v.side_delta_y - game->player.y) * (ray_v.side_delta_y - game->player.y)));

	if (ray_h_d < ray_v_d)
		draw_line_dda(game, ray_h.side_delta_x, ray_h.side_delta_y, angle);
	else
		draw_line_dda(game, ray_v.side_delta_x, ray_v.side_delta_y, angle);

}
