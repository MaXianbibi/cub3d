/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 23:24:54 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/30 00:36:07 by jmorneau         ###   ########.fr       */
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
void scale(t_data *img, t_data *img_texture, float lineH, int pixel, float ty_off, t_mlx *game)
{
	int i;
	int color;
	(void)ty_off;
	
	float stepx = 0;
	
	if 		((game->ray[pixel].hit_down && game->ray[pixel].hit_left) || (!game->ray[pixel].hit_down && !game->ray[pixel].hit_left))
		stepx = fmod(game->ray[pixel].side_delta_x, 64);
	else
		stepx = fmod(game->ray[pixel].side_delta_y, 64);
	stepx = (stepx * 1.875);

	float lineO = (HEIGHT / 2.0) - lineH / 2.0;
	float bon = 120.0 / lineH;
	// float bon = ty_off;
	// float stepy = ty_off;
	float stepy = 0;
	// stepy *= -1;

	i = 0;
	while (i < lineH)
	{
		color = get_pixel(img_texture, stepx, stepy);
		my_mlx_pixel_put(img, pixel + WIDTH, i + lineO, color);
		stepy += bon;
		i++;
	}
	// printf("%d\n", pixel);
}