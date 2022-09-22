/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 23:24:54 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/22 19:21:42 by jmorneau         ###   ########.fr       */
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
	if (x >= 1920 || x < 0 || y >= 1080 || y < 0)
		return 0;
	
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));

	return *(unsigned int *)dst;
}

void scale(t_data *img, float scale, float stepx, t_data *img2)
{
	float image = 120.0 * scale;
	float bon = 120.0 / image;
	float stepi = 0;
	int color;
	int i = 0;

	float lineO = (HEIGHT / 2.0) - image/2.0;
	while (i < image)
	{
		color = get_pixel(img2, stepx * bon , stepi);
		my_mlx_pixel_put(img, (stepx) + WIDTH, i + lineO, color);
		stepi += bon;
		i++;
	}
}