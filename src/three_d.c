/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 00:58:59 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/22 19:37:26 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_walls(t_mlx *game, t_ray ray, int pixel_x, float angle)
{
	int color = RED;
	float ca = angle - game->player.rotation_angle ;
	ray.dist = ray.dist * cos(ca);
	float lineH = (32 * HEIGHT) / ray.dist;
	if (lineH > HEIGHT)
		lineH = HEIGHT;
	int i;
	float lineO = (HEIGHT / 2) - lineH/2;
	i = 0;

	if 		(ray.hit_down && ray.hit_left) // down
			color = BRL;
	else if (ray.hit_left && !ray.hit_down) // left
			color = BRS;
	else if (!ray.hit_left && ray.hit_down) // right
			color = BRS;
	else if (!ray.hit_down && !ray.hit_left) // up
			color = BRL;
	while (i < lineH)
		my_mlx_pixel_put(&game->img, pixel_x + WIDTH, i++ + lineO, color);
		


	// float scale_l = (lineH / HEIGHT);
	
	// printf("%f\n", scale_l);

	// for (int j = 0; j < HEIGHT * scale_l; j++)
	// {
		
		// scale(&game->img, scale_l, pixel_x, &game->texture.nort);
		// scale_l -= 0.025;
	// }
}