/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 03:41:41 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/17 02:50:54 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_square(t_mlx *game, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			if ((i == 0 || j == 0 || i == 63 || j == 63))
				my_mlx_pixel_put(&game->img, j++ + x, i + y, BG);
			else
				my_mlx_pixel_put(&game->img, j++ + x, i + y, color);
		}
		i++;
	}
}

void draw_grid(t_mlx *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->map.col)
	{
		j = 0;
		while (j < game->map.raw)
		{
			if (game->map.map[i][j] == '1')
				draw_square(game, j * 64, i * 64, BLK);
			else
				draw_square(game, j * 64, i * 64, WHT);
			j++;
		}
		i++;
	}
}
