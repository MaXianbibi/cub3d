/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_interaction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 01:58:49 by jmorneau          #+#    #+#             */
/*   Updated: 2022/10/17 19:00:19 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int move_player(t_mlx *game)
{
	if (game->key_hook.a)
			game->player.rotation_angle += game->player.turn_speed;
	if (game->key_hook.d)
			game->player.rotation_angle -= game->player.turn_speed;
	if (game->key_hook.w)
	{
		game->player.x += cos(game->player.rotation_angle) * game->player.walk_speed;
		game->player.y -= sin(game->player.rotation_angle) * game->player.walk_speed;
	}
	if (game->key_hook.s)
	{
		game->player.x -= cos(game->player.rotation_angle) * game->player.walk_speed;
		game->player.y += sin(game->player.rotation_angle) * game->player.walk_speed;
	}

	back_ground(game);
	return (0);
}

static void open_door(t_mlx *game)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	if 		(game->ray[(int)WIDTH / 2].hit_down && game->ray[(int)WIDTH / 2].hit_left)
			i = 1;
	else if 		(game->ray[(int)WIDTH / 2].hit_down && !game->ray[(int)WIDTH / 2].hit_left)
			j = 1;
	else if 		(!game->ray[(int)WIDTH / 2].hit_down && game->ray[(int)WIDTH / 2].hit_left)
			j = -1;
	else if 		(!game->ray[(int)WIDTH / 2].hit_down && !game->ray[(int)WIDTH / 2].hit_left)
			i = -1; 
	if (mapHasDoor(game, (((int)game->player.x >> 6) + j), ((int)game->player.y >> 6) + i) == 1 && game->ray[(int)WIDTH / 2].door.is_a_door == 1)
	{
		game->map.map[((int)game->player.y >> 6) + i][((int)game->player.x >> 6) + j] = 'A';
		game->frames = 0;
	}
	else if (game->map.map[((int)game->player.y >> 6) + i][((int)game->player.x >> 6) + j] == 'Z')
	{
		game->map.map[((int)game->player.y >> 6) + i][((int)game->player.x >> 6) + j] = 'O';
		game->frames = 0;
	}

	i = 0;
	

	// printf("%d\n", game->frames);
}

int	move(int keycode, t_mlx *game)
{	
	if (keycode == A)
		game->key_hook.a = 1;
	else if (keycode == D)
		game->key_hook.d = 1;
	else if (keycode == W)
		game->key_hook.w = 1;
	else if (keycode == S)
		game->key_hook.s = 1;
	else if (keycode == SHIFT)
	{
		game->player.walk_speed = 6;
		game->player.turn_speed *= 1.5;
	}
	else if (keycode == ESC)
		destroy_image(game);
	return (0);
}
int	check_key_is_on(int keycode, t_mlx *game)
{	
	if (keycode == A)
		game->key_hook.a = 0;
	else if (keycode == D)
		game->key_hook.d = 0;
	else if (keycode == W)
		game->key_hook.w = 0;
	else if (keycode == S)
		game->key_hook.s = 0;
	else if (keycode == SHIFT)
	{
		game->player.walk_speed = 3;
		game->player.turn_speed /= 1.5;
	}
 	if (keycode == E)
		open_door(game);
		
	return (0);
}