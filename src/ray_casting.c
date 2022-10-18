/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 02:37:39 by jmorneau          #+#    #+#             */
/*   Updated: 2022/10/18 17:36:47 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int mapHasWallAt(t_mlx *game , int x, int y) {
    if (x < 0 || x > (WIDTH / 64) - 1 || y < 0 || y > (HEIGHT / 64) - 1) {
        return 1;
    }
	if (game->map.map[y][x] == '1')
		return (1);
    return (0);
}

int mapHasDoor(t_mlx *game , int x, int y) {
    if (x < 0 || x > (WIDTH / 64) - 1 || y < 0 || y > (HEIGHT / 64) - 1) {
        return 1;
    }

	
	if (game->map.map[y][x] == '2')
		return (1);
	if (game->map.map[y][x] == 'A' || game->map.map[y][x] == 'Z' || game->map.map[y][x] == 'O')
		return (2);
    return (0);
}

void draw_fov(t_mlx *game)
{
	float cangle = game->player.rotation_angle;
	float j = cangle - FOV_ANGLE;
	int i;

	i = 0;
	while (cangle > j)
	{
		game->ray[i] = dda_v2(game, cangle + (FOV_ANGLE / 2));
		draw_walls_beta(game, game->ray[i], i, cangle + (FOV_ANGLE / 2));

			// printf("%d\n", game->ray[i].door.is_a_door);
		if (game->ray[i].door.is_a_door)
		{
			draw_door_beta(game, game->ray[i], i, cangle + (FOV_ANGLE / 2));
		}
		cangle -= FOV_ANGLE / NUM_RAY;
		i++;
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
	t_ray ray = { 0 };

	ra = normalize_angle(angle);
	if (ra < PI)
	{
		ry = (((int)game->player.y >> 6) << 6) - 0.0001;
		rx = game->player.x - ((game->player.y - ry) * aTan);		
		yo = -64;
		xo = (yo * aTan);
		ray.hit_down = 0;
		ray.hit_left = 0;
	}
	else if (ra > PI)
	{
		ry = (((int)game->player.y >> 6) << 6) + 64;
		rx = game->player.x - ((game->player.y - ry) * aTan);
		yo = 64;
		xo = yo * aTan;
		ray.hit_down = 1;
		ray.hit_left = 1;
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
		if (mapHasWallAt(game, mx, my))
			break;
			
		int door = mapHasDoor(game, mx, my);

		if ( door )
		{
			ray.door.is_a_door = door;
			ray.door.door_location.x = rx;
			ray.door.door_location.y = ry;

			if (!ray.hit_left && !ray.hit_down)
				ray.door.starting_x = (((int)ray.door.door_location.x  >> 6) << 6) - 0.0001;
			else
				ray.door.starting_x = (((int)ray.door.door_location.x  >> 6) << 6) + 64;

			

			ray.door.dist_door = sqrtf(((rx - game->player.x) * (rx - game->player.x)) + ((ry - game->player.y) * (ry - game->player.y)));
		// printf("%d\n", ray.door.is_a_door);
		}
		rx += xo;
		ry += yo;
	}
	
	ray.side_delta_x = rx;
	ray.side_delta_y = ry;
	// ray.is_a_door = mapHasDoor(game, mx, my);
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

	t_ray ray = { 0 };

	ra = normalize_angle(angle);
	if (ra > QUART_PI && ra < QUART3_PI)
	{
		rx = (((int)game->player.x >> 6) << 6) - 0.0001;
		ry =  game->player.y - ((game->player.x - rx) * nTan) ;		
		xo = -64;
		yo = (xo * nTan);
		ray.hit_left = 1;
		ray.hit_down = 0;
	}
	else if (ra < QUART_PI || ra > QUART3_PI)
	{
		rx = (((int)game->player.x >> 6) << 6) + 64;
		ry = game->player.y - ((game->player.x - rx) * nTan) ;
		xo = 64;
		yo = xo * nTan;
		ray.hit_left = 0;
		ray.hit_down = 1;
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

		// ray.door.is_a_door = mapHasDoor(game, mx, my);
		if ( mapHasDoor(game, mx, my) )
		{	
			
			ray.door.door_location.x = rx + 32;
			ray.door.door_location.y = ry + 32;


			if (ra > QUART_PI && ra < QUART3_PI)
				ray.door.starting_x = (((int)ray.door.door_location.x  >> 6) << 6) - 0.0001;
			else
				ray.door.starting_x = (((int)ray.door.door_location.x  >> 6) << 6) + 64;	
				

			
			ray.door.dist_door = sqrtf(((rx - game->player.x) * (rx - game->player.x)) + ((ry - game->player.y) * (ry - game->player.y)));
		}
	
		rx += xo;
		ry += yo;
	}
	

	ray.side_delta_x = rx;
	ray.side_delta_y = ry;
	return (ray);
}

t_ray dda_v2(t_mlx *game, float angle)
{
	t_ray	ray_h = dda_h(game, angle);
	t_ray	ray_v = dda_v(game, angle);
	
	ray_h.dist = sqrtf(((ray_h.side_delta_x - game->player.x) * (ray_h.side_delta_x - game->player.x)) + ((ray_h.side_delta_y - game->player.y) * (ray_h.side_delta_y - game->player.y)));
	ray_v.dist = sqrtf(((ray_v.side_delta_x - game->player.x) * (ray_v.side_delta_x - game->player.x)) + ((ray_v.side_delta_y - game->player.y) * (ray_v.side_delta_y - game->player.y)));
	
	// ray_h.dist = Q_rsqrt(((ray_h.side_delta_x - game->player.x) * (ray_h.side_delta_x - game->player.x)) + ((ray_h.side_delta_y - game->player.y) * (ray_h.side_delta_y - game->player.y)));
	// ray_v.dist = Q_rsqrt(((ray_v.side_delta_x - game->player.x) * (ray_v.side_delta_x - game->player.x)) + ((ray_v.side_delta_y - game->player.y) * (ray_v.side_delta_y - game->player.y)));

	


	if (ray_h.door.is_a_door && !ray_v.door.is_a_door)
		ray_v.door = ray_h.door;
	else //if (ray_v.door.is_a_door && (ray_v.door.dist_door < ray_h.dist) && (ray_h.door.dist_door < ray_v.dist) )
		ray_h.door = ray_v.door;
	
	if (ray_h.dist < ray_v.dist)
	{
			if ( ray_h.door.dist_door > ray_h.dist)
				ray_h.door.is_a_door ^= ray_h.door.is_a_door;
			draw_line_dda(game, ray_h.side_delta_x, ray_h.side_delta_y, angle);
			return (ray_h);
	}
			draw_line_dda(game, ray_v.side_delta_x, ray_v.side_delta_y, angle);
			if ( ray_v.door.dist_door > ray_v.dist)
				ray_v.door.is_a_door ^= ray_v.door.is_a_door;
			return (ray_v);

}
