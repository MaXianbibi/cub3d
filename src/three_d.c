/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 00:58:59 by jmorneau          #+#    #+#             */
/*   Updated: 2022/10/18 17:24:45 by jmorneau         ###   ########.fr       */
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
	float lineO = ((HEIGHT / 2.0) - lineH / 2.0);
	// float lineO = 0;
	float stepy = ty_off * ty_step;
	float stepx = 0;

	if 		((game->ray[pixel_x].hit_down && game->ray[pixel_x].hit_left) || (!game->ray[pixel_x].hit_down && !game->ray[pixel_x].hit_left))
		stepx = fmod(game->ray[pixel_x].side_delta_x, WIDTH_ASSET);
	else
		stepx = fmod(game->ray[pixel_x].side_delta_y, WIDTH_ASSET);
	stepx = (stepx * (img->img_width / WIDTH_ASSET));	

	if 		((ray.hit_down && ray.hit_left) || (ray.hit_left && !ray.hit_down)) // down
		print_texture(&game->img, img, img->img_height - stepx, stepy, lineO, ty_step, lineH, pixel_x, game, angle);
	else
		print_texture(&game->img, img, stepx, stepy, lineO, ty_step, lineH, pixel_x, game, angle);
}

void draw_door_beta(t_mlx *game, t_ray ray, int pixel_x, float angle)
{

	ray.door.dist_door = ray.door.dist_door * cos(angle - game->player.rotation_angle);

	// printf("%c\n", game->map.map[((int)ray.door.door_location.y >> 6)][((int)ray.door.door_location.x >> 6)]);
	// printf("%d\n", game->frames);
	
	// printf("%d - %d = %d\n", (int)ray.door.door_location.x, (int)ray.door.starting_x, (int)ray.door.door_location.x - ray.door.starting_x);
	if (game->map.map[((int)ray.door.door_location.y >> 6)][((int)ray.door.door_location.x >> 6)] == 'A' && (fabsf(ray.door.door_location.x - ray.door.starting_x) > 64 - game->frames))
	{
		if (game->frames >= 64)
			game->map.map[((int)ray.door.door_location.y >> 6)][((int)ray.door.door_location.x >> 6)] = 'Z';
		return ;
	}
	if (game->map.map[((int)ray.door.door_location.y >> 6)][((int)ray.door.door_location.x >> 6)] == 'O' && fabsf(ray.door.door_location.x - ray.door.starting_x ) > game->frames)
		return ;
	if (game->map.map[((int)ray.door.door_location.y >> 6)][((int)ray.door.door_location.x >> 6)] != 'O' && game->map.map[((int)ray.door.door_location.y >> 6)][((int)ray.door.door_location.x >> 6)] != '2' && game->map.map[((int)ray.door.door_location.y >> 6)][((int)ray.door.door_location.x >> 6)] != 'A')
		return ;
	if (game->frames >= 64)
		game->map.map[((int)ray.door.door_location.y >> 6)][((int)ray.door.door_location.x >> 6)] = '2';
	float lineH = (WIDTH_ASSET * HEIGHT) / ray.door.dist_door;
	t_data *img = &game->texture.door;
	
	float ty_step = (img->img_height / lineH);
	
	if (img->img_height > HEIGHT)
		ty_step *= HEIGHT / img->img_height;
	float ty_off = 0;
	if (lineH > HEIGHT)
	{
		ty_off =  (lineH - HEIGHT) / 2.0;
		lineH = HEIGHT;
	}
	float lineO = ((HEIGHT / 2.0) - lineH / 2.0);
	// float lineO = 0;
	float stepy = ty_off * ty_step;
	float stepx = 0;

	if 		((game->ray[pixel_x].hit_down && game->ray[pixel_x].hit_left) || (!game->ray[pixel_x].hit_down && !game->ray[pixel_x].hit_left))
		stepx = fabs(fmod(game->ray[pixel_x].door.door_location.x, WIDTH_ASSET));
	else
		stepx = fabs(fmod(game->ray[pixel_x].door.door_location.x, WIDTH_ASSET));



	if (game->map.map[((int)ray.door.door_location.y >> 6)][((int)ray.door.door_location.x >> 6)] == 'A' )
		stepx = stepx - game->frames;
	else if ( game->map.map[((int)ray.door.door_location.y >> 6)][((int)ray.door.door_location.x >> 6)] == 'O')
		stepx = stepx + game->frames - 64;
	stepx = (stepx * (img->img_width / WIDTH_ASSET));	




	if 		((ray.hit_down && ray.hit_left) || (ray.hit_left && !ray.hit_down))
		print_texture_door(&game->img, img, stepx, stepy, lineO, ty_step, lineH, pixel_x, game);
	else  
		print_texture_door(&game->img, img, stepx, stepy, lineO, ty_step, lineH, pixel_x, game);

}

