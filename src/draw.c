/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 03:29:11 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/17 02:49:07 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float convert_deg_rad(float deg)
{
	return (deg * (PI / 180.0));
}

float convert_rad_deg(float rad)
{
	return (rad * (180 / PI));
}

void draw_player(t_mlx *game, int color)
{
	int i;
	int j;

	i = 0;
	while (i < game->player.height)
	{
		j = 0;
		while (j < game->player.withd)
			my_mlx_pixel_put(&game->img, game->player.x + j++, game->player.y + i, color);	
		i++;
	}
}

void back_ground(t_mlx *game)
{
	int i;
	int j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			my_mlx_pixel_put(&game->img, j++, i, BG);	
		i++;
	}
	draw_grid(game);
	draw_player(game, RED);
	draw_fov(game);
	mlx_put_image_to_window(game->basic.mlx, game->basic.win, game->img.img, 0, 0);
}


