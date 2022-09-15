/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 03:41:41 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/15 18:10:35 by jmorneau         ###   ########.fr       */
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
			my_mlx_pixel_put(&game->img, j++ + x, i + y, color);
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
				draw_square(game, j * 64 + j * 2, i * 64 + i * 2, BLK);
			else
				draw_square(game, j * 64 + j * 2, i * 64 + i * 2, WHT);
			j++;
		}
		i++;
	}
}
