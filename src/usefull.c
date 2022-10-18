/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 23:24:54 by jmorneau          #+#    #+#             */
/*   Updated: 2022/10/18 17:10:36 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float mod_negatif(float n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

float normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

int get_pixel(t_data *data, int x, int y)
{
	if (x >= data->img_width || x < 0 || y >= data->img_height || y < 0)
		return 0;

	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));

	return *(unsigned int *)dst;
}

void print_texture(t_data *img, t_data *img_texture, float stepx, float stepy, float lineO, float ty_step, float lineH, float pixel_x, t_mlx *game, float angle)
{
	int i = 0;
	int color;
	float directionCos = cos(angle);
	float directionSin = sin(angle);
	float tileX;
	float tileY;

	float cstepy = stepy;

	//  wall texture
	
	while (i < lineH)
	{
		color = get_pixel(img_texture, stepx, cstepy);
		my_mlx_pixel_put(img, pixel_x + WIDTH, i + lineO, color);
		cstepy += ty_step;
		i++;
	}
	i += lineO;
	int y = HEIGHT;
	while (y > i)
	{

		// floor casting

		float distance = (HEIGHT) / (2.f * y - (HEIGHT)); // ou z
		distance = distance / cos(angle - game->player.rotation_angle);

		tileX = distance * directionCos;
		tileY = distance * directionSin;

		tileX += ((game->player.x / 64)  + 64);
		tileY -= ((game->player.y / 64) - 64);

		int texture_x;
		int texture_y;

		// floor texture

		texture_x = floorf(tileX * game->texture.floor.img_width);
		texture_x %= (int)game->texture.floor.img_width;

		texture_y = floorf(tileY * game->texture.floor.img_height);
		texture_y %= (int)game->texture.floor.img_width;

		
		color = get_pixel(&game->texture.floor, texture_x, texture_y);
		my_mlx_pixel_put(img, pixel_x + WIDTH, y, color - 275);

		// celling texture

		texture_x = floorf(tileX * game->texture.celling.img_width);
		texture_x %= (int)game->texture.celling.img_width;

		texture_y = floorf(tileY * game->texture.celling.img_height);
		texture_y %= (int)game->texture.celling.img_width;

		color = get_pixel(&game->texture.celling, texture_x, texture_y);
		my_mlx_pixel_put(img, pixel_x + WIDTH, HEIGHT - y, color);


		y--;
	}
	// printf("%f %f\n", tx, ty);
}


void print_texture_door(t_data *img, t_data *img_texture, float stepx, float stepy, float lineO, float ty_step, float lineH, float pixel_x, t_mlx *game)
{
	int i = 0;
	int color;

	float cstepy = stepy;	
	color = RED;
	// (void)img_texture;
	(void)game;
	while (i < lineH)
	{
		// color = get_pixel(img_texture, stepx, cstepy);

		color = get_pixel(img_texture, stepx, cstepy);
		my_mlx_pixel_put(img, pixel_x + WIDTH, i + lineO, color);
		cstepy += ty_step;
		i++;
	}
	
}






t_data *cardinal_points(t_ray *ray, t_mlx *game)
{
	// if (ray->is_a_door)
	// 	return (&game->texture.door);
	if (ray->hit_down && ray->hit_left) // down
		return (&game->texture.nort);
	else if (ray->hit_left && !ray->hit_down) // left
		return (&game->texture.west);
	else if (!ray->hit_left && ray->hit_down) // right
		return (&game->texture.east);
	else if (!ray->hit_down && !ray->hit_left) // up
		return (&game->texture.south);
	return (NULL);
}
