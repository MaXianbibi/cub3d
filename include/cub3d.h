/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:40:03 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/15 18:10:24 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft.h"
# include <mlx.h>
# include <stdbool.h>
# include <math.h>
# define PI 3.14159265359


// COLORS

# define YLW 	0xFFFF00
# define BG	 	0xA6A6A6
# define WHT	0xFFFFFF
# define BLK	0

// KEY
# define D 2
# define A 0
# define W 1
# define S 13
# define ESC 53

typedef struct	s_player
{
	float		px;
	float 		py;
	float		pdx;
	float		pdy;
	float		pa;

}				t_player;

typedef struct	s_map
{
	char		**map;
	int			col;
	int			raw;
}				t_map;

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_basic
{
	void		*mlx;
	void		*win;
}	t_basic;

typedef struct s_mlx
{
	t_basic		basic;
	t_data		img;
	t_player	player;
	t_map		map;
}	t_mlx;

void 	image_init(t_mlx *game);
int		move(int keycode, t_mlx *game);
void 	draw_player(t_mlx *game, int color);
bool	map_reader(char *file, t_mlx *game);
void	back_ground(t_mlx *game);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_square(t_mlx *game, int x, int y, int color);
void	draw_grid(t_mlx *game);

#endif