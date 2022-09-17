/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_interaction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 01:58:49 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/17 03:10:02 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	move(int keycode, t_mlx *game)
{
	if (keycode == A)
		game->player.rotation_angle += game->player.turn_speed;
	else if (keycode == D)
		game->player.rotation_angle -= game->player.turn_speed;
	else if (keycode == W)
	{
		game->player.x += cos(game->player.rotation_angle) * 10;
		game->player.y -= sin(game->player.rotation_angle) * 10;
	}
	else if (keycode == S)
	{
		game->player.x -= cos(game->player.rotation_angle) * 10;
		game->player.y += sin(game->player.rotation_angle) * 10;
	}
	else if (keycode == ESC)
		destroy_image(game);
		
	back_ground(game);
		// draw_fov(game);
	return (0);
}

		// game->player.py += 8;
		// game->player.px += 8;