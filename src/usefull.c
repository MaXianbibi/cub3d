/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 23:24:54 by jmorneau          #+#    #+#             */
/*   Updated: 2022/10/02 03:52:59 by jmorneau         ###   ########.fr       */
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

void print_texture(t_data *img, t_data *img_texture, float stepx, float stepy, float lineO, float ty_step, float lineH, float pixel_x)
{
	int i = 0;
	int color;

	while (i < lineH)
	{
		color = get_pixel(img_texture,	stepx, stepy);
		my_mlx_pixel_put(img, pixel_x + WIDTH, i + lineO, color);
		stepy += ty_step;
		i++;
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
