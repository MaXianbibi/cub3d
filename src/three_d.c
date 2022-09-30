/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 00:58:59 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/30 00:33:25 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_walls(t_mlx *game, t_ray ray, int pixel_x, float angle)
{
	// int color = RED;
	
	float ca = angle - game->player.rotation_angle ;
	ray.dist = ray.dist * cos(ca);
	
	float lineH = ((64.0) * HEIGHT) / ray.dist; // 1.5 == zoom 
	float ty_step = 120.0 / lineH;
	float ty_off = 0;
	if (lineH > HEIGHT)
	{
		ty_off =  (lineH - HEIGHT) / 2.0;
		lineH = HEIGHT;
	}
	
	float ty = ty_off * ty_step;
	
	printf("%f\n", ty);
	int i;

	i = 0;
	scale(&game->img, &game->texture.nort, lineH, pixel_x, ty, game);		
}

void draw_walls_beta(t_mlx *game, t_ray ray, int pixel_x, float angle)
{
	int color;
	
	float ca = angle - game->player.rotation_angle;
	ray.dist = ray.dist * cos(ca);
	
	float lineH = (WIDTH_ASSET * HEIGHT) / ray.dist;
	float ty_step = (game->texture.nort.img_height / lineH);
	
	if (game->texture.nort.img_height > HEIGHT)
		ty_step *= HEIGHT / game->texture.nort.img_height;
	// printf("%f / %f\n", game->texture.nort.img_height, lineH);
	float ty_off = 0;
	if (lineH > HEIGHT)
	{
		ty_off =  (lineH - HEIGHT) / 2.0;
		lineH = HEIGHT;
	}
	float lineO = (HEIGHT / 2.0) - lineH / 2.0;
	
	int i = 0;
	float stepy = ty_off * ty_step;
	float stepx = 0;

	if 		((game->ray[pixel_x].hit_down && game->ray[pixel_x].hit_left) || (!game->ray[pixel_x].hit_down && !game->ray[pixel_x].hit_left))
		stepx = fmod(game->ray[pixel_x].side_delta_x, WIDTH_ASSET);
	else
		stepx = fmod(game->ray[pixel_x].side_delta_y, WIDTH_ASSET);
	stepx = (stepx * (game->texture.nort.img_width / WIDTH_ASSET));



	while (i < lineH)
	{
		color = get_pixel(&game->texture.nort,	stepx, stepy);
		my_mlx_pixel_put(&game->img, pixel_x + WIDTH, i + lineO, color);
		stepy += ty_step;
		i++;
	}
		
}


	// float lineO = (HEIGHT / 2.0) - lineH / 2.0;



	// if 		(ray.hit_down && ray.hit_left) // down
	// {
	// }
	// else if (ray.hit_left && !ray.hit_down) // left
	// 		color = BRS;
	// else if (!ray.hit_left && ray.hit_down) // right
	// 		color = BRS;
	// else if (!ray.hit_down && !ray.hit_left) // up
	// 		color = BRL;
	// while (i < lineH)
	// {
	// 	if (color != RED)
	// 		my_mlx_pixel_put(&game->img, pixel_x + WIDTH, i + lineO, color);
	// 	i++;
	// }