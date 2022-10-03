/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 23:24:54 by jmorneau          #+#    #+#             */
/*   Updated: 2022/10/03 18:01:48 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

int get_pixel(t_data *data, int x, int y)
{
	if (x >= WIDTH_TEST || x < 0 || y >= HEIGHT || y < 0)
		return 0;
	
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));

	return *(unsigned int *)dst;
}

void print_texture(t_data *img, t_data *img_texture, float stepx, float stepy, float lineO, float ty_step, float lineH, float pixel_x, t_mlx *game, float angle)
{
	int i = 0;
	int color;

	float cstepy = stepy;
	while (i < lineH)
	{
		color = get_pixel(img_texture,	stepx, cstepy);
		my_mlx_pixel_put(img, pixel_x + WIDTH, i + lineO, color);
		cstepy += ty_step;
		i++;
	}
	i += lineO;
	cstepy = stepy;

	// float dy;
	// float dx;
	int j = 0;
	(void)game;
	(void)angle;
	while (i < HEIGHT)
	{
		// dy = i - (j - sin(angle - game->player.rotation_angle));
		// dx = i - (j + cos(angle - game->player.rotation_angle));
		 	
		// if ((int)pixel_x % 3 == 0)
			// my_mlx_pixel_put(img, pixel_x + WIDTH, i, RED);
		// else if ((int)pixel_x % 3 == 1)
			// my_mlx_pixel_put(img, pixel_x + WIDTH, i, GRN);
		// else if ((int)pixel_x % 3 == 2)
			// my_mlx_pixel_put(img, pixel_x + WIDTH, i, BLU);
		i++;
		j++;
	}
	
	
}

t_data *cardinal_points(t_ray *ray, t_mlx *game)
{
	if (ray->is_a_door)
			return (&game->texture.door);
	if 		(ray->hit_down && ray->hit_left) // down
			return (&game->texture.nort);
	else if (ray->hit_left && !ray->hit_down) // left
			return (&game->texture.west);
	else if (!ray->hit_left && ray->hit_down) // right
			return (&game->texture.east);
	else if (!ray->hit_down && !ray->hit_left) // up
			return (&game->texture.south);
	return (NULL);
}
