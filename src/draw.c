/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 03:29:11 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/15 17:51:50 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_ray(t_mlx *game, int color)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 8)
			my_mlx_pixel_put(&game->img, (game->player.px + game->player.pdx * 5)+ j++, (game->player.py + game->player.pdy * 5) + i, color);	
		i++;
	}
}

void back_ground(t_mlx *game)
{
	int i;
	int j;

	i = 0;
	while (i < 1080)
	{
		j = 0;
		while (j < 1920)
			my_mlx_pixel_put(&game->img, j++, i, BG);	
		i++;
	}
	draw_grid(game);
	mlx_put_image_to_window(game->basic.mlx, game->basic.win, game->img.img, 0, 0);
}

void draw_player(t_mlx *game, int color)
{
	int i;
	int j;

	i = 0;
	while (i < 16)
	{
		j = 0;
		while (j < 16)
			my_mlx_pixel_put(&game->img, game->player.px + j++, game->player.py + i, color);	
		i++;
	}
	draw_ray(game, YLW);
	mlx_put_image_to_window(game->basic.mlx, game->basic.win, game->img.img, 0, 0);
}


