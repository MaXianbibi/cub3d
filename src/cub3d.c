/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 01:51:59 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/15 17:17:49 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void game_init(t_mlx *game)
{
	game->player.px = 296;
	game->player.py = 296;
	game->player.pa = 0;
	game->player.pdx = cos(game->player.pa) * 5;
	game->player.pdy = sin(game->player.pa) * 5;
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