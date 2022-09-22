/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 01:57:08 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/22 19:16:29 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	destroy_image(t_mlx *game)
{
		mlx_destroy_image(game->basic.mlx, &game->img);
		ft_free_chartable(game->map.map);
		free(game->ray);
		exit(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	
	if (x >= WIDTH_TEST || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void image_init(t_mlx *game)
{	
	game->basic.mlx = mlx_init();
	// game->basic.win = mlx_new_window(game->basic.mlx, 64 * game->map.raw, 64 * game->map.col + game->map.col * 2, "cub3d");
	// game->img.img = mlx_new_image(game->basic.mlx, 64 * game->map.raw + game->map.raw * 2, 64 * game->map.col + game->map.col * 2);

	game->basic.win = mlx_new_window(game->basic.mlx, WIDTH_TEST, HEIGHT, "cub3d");
	game->img.img = mlx_new_image(game->basic.mlx, WIDTH_TEST, HEIGHT);
	
	
	
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length,
								&game->img.endian);
	back_ground(game);
	draw_player(game, YLW);
	mlx_hook(game->basic.win, 2, 1L << 0, move, game);
	mlx_hook(game->basic.win, 17, 0, (void *)exit, 0);
	mlx_loop(game->basic.mlx);
}