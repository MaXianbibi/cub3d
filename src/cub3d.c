/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 01:51:59 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/22 19:50:14 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	texture_init(t_mlx *game)
{
	char *relative_path = "./texture/void.xpm";

	int img_width;
	int img_height;

	game->texture.nort.img = mlx_xpm_file_to_image(game->basic.mlx, relative_path, &img_width, &img_height);
	
	// game->texture.nort.addr = mlx_get_data_addr(game->texture.nort.img, &game->texture.nort.bits_per_pixel, &game->texture.nort.line_length,
								//   &game->texture.nort.endian);
								  
	// game->texture.nort.height = img_height;
	// game->texture.nort.width = img_width;
}

static void game_init(t_mlx *game)
{
	game->player.x = WIDTH / 2;
	game->player.y = HEIGHT / 2;
	game->player.withd = 1;
	game->player.height = 1;
	game->player.turn_direction = 0;
	game->player.walk_direction = 0;
	game->player.rotation_angle = PI * 3 / 2;
	game->player.walk_speed = 100;
	game->player.turn_speed = convert_deg_rad(5);
	game->ray = malloc(sizeof(t_ray) * NUM_RAY);
	game->map.col = 0;
	game->map.raw = 0;
	game->map.map = NULL;
	texture_init(game);
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
		free(game.ray);
		return (0);
	}
	// map reader
	// map parser
	image_init(&game);
}