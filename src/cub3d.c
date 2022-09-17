/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 01:51:59 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/17 03:11:10 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void game_init(t_mlx *game)
{
	game->player.x = WIDTH / 2;
	game->player.y = HEIGHT / 2;
	game->player.withd = 1;
	game->player.height = 1;
	game->player.turn_direction = 0;
	game->player.walk_direction = 0;
	game->player.rotation_angle = PI;
	game->player.walk_speed = 100;
	game->player.turn_speed = convert_deg_rad(5);
	
	game->map.col = 0;
	game->map.raw = 0;
	game->map.map = NULL;
}

int main(int argc, char **argv)
{
	t_mlx game;

	if (argc != 2)
		return (ft_print_error("Il faut 2 arguments\n"));
	game_init(&game);
	if (map_reader(argv[1], &game))
	{
		ft_free_chartable(game.map.map);
		return (0);
	}
	// map reader
	// map parser
	image_init(&game);
}