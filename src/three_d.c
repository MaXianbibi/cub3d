/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 00:58:59 by jmorneau          #+#    #+#             */
/*   Updated: 2022/10/01 23:54:40 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_walls_beta(t_mlx *game, t_ray ray, int pixel_x, float angle)
{
	ray.dist = ray.dist * cos(angle - game->player.rotation_angle);
	
	float lineH = (WIDTH_ASSET * HEIGHT) / ray.dist;
	t_data *img = cardinal_points(&ray, game);
	float ty_step = (img->img_height / lineH);
	if (img->img_height > HEIGHT)
		ty_step *= HEIGHT / img->img_height;
	float ty_off = 0;
	if (lineH > HEIGHT)
	{
		ty_off =  (lineH - HEIGHT) / 2.0;
		lineH = HEIGHT;
	}
	float lineO = (HEIGHT / 2.0) - lineH / 2.0;
	float stepy = ty_off * ty_step;
	float stepx = 0;

	// au debut, changer l'img selon le.. ez
	if 		((game->ray[pixel_x].hit_down && game->ray[pixel_x].hit_left) || (!game->ray[pixel_x].hit_down && !game->ray[pixel_x].hit_left))
		stepx = fmod(game->ray[pixel_x].side_delta_x, WIDTH_ASSET);
	else
		stepx = fmod(game->ray[pixel_x].side_delta_y, WIDTH_ASSET);
	stepx = (stepx * (img->img_width / WIDTH_ASSET));
	
		// print_texture(&game->img, img, stepx, stepy, lineO, ty_step, lineH, pixel_x);
	if 		(ray.hit_down && ray.hit_left) // down
		print_texture(&game->img, img, img->img_height - stepx, stepy, lineO, ty_step, lineH, pixel_x);
	else if (ray.hit_left && !ray.hit_down) // left
		print_texture(&game->img, img, img->img_height - stepx, stepy, lineO, ty_step, lineH, pixel_x);
	else if (!ray.hit_left && ray.hit_down) // right
		print_texture(&game->img, img, stepx, stepy, lineO, ty_step, lineH, pixel_x);
	else if (!ray.hit_down && !ray.hit_left) // up
		print_texture(&game->img, img, stepx, stepy, lineO, ty_step, lineH, pixel_x);

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