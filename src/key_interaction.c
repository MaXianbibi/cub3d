/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_interaction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 01:58:49 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/15 17:52:17 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	move(int keycode, t_mlx *game)
{
	back_ground(game);
	if (keycode == A)
	{
		game->player.pa -= 0.1;
		if (game->player.pa < 0)
			game->player.pa += 2*PI;
		game->player.pdx = cos(game->player.pa) * 5;
		game->player.pdy = sin(game->player.pa) * 5;
	}
	else if (keycode == D)
	{
		game->player.pa += 0.1;
		if (game->player.pa > 2 * PI)
			game->player.pa = 0;
		game->player.pdx = cos(game->player.pa) * 5;
		game->player.pdy = sin(game->player.pa) * 5;
	}
	else if (keycode == S)
	{
		game->player.px += game->player.pdx;
		game->player.py += game->player.pdy;
	}
	else if (keycode == W)
	{
		game->player.px -= game->player.pdx;
		game->player.py -= game->player.pdy;
	}
	else if (keycode == ESC)
	{
		mlx_destroy_image(game->basic.mlx, game->basic.win);
		exit(0);
	}
	draw_player(game, YLW);
	return (0);
}

		// game->player.py += 8;
		// game->player.px += 8;