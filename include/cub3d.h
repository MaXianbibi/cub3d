/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:40:03 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/30 18:36:12 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft.h"
# include <mlx.h>
# include <stdbool.h>
# include <math.h>

// a sup
# include <stdio.h>

# define PI 			3.14159265359
# define TWO_PI 		6.28318530718
# define QUART_PI		PI / 2
# define QUART3_PI		3 * PI / 2


# define WIDTH 			640.0
# define HEIGHT 		448.0

# define WIDTH_TEST		WIDTH * 2

# define FOV_ANGLE		(66 * (PI / 180))
# define NUM_RAY		WIDTH
# define WIDTH_ASSET	64.0

// COLORS

# define YLW 			0xFFFF00
# define BG	 			0xA6A6A6
# define WHT			0xFFFFFF
# define GRN			0x00FF00
# define RED			0xFF0000
# define BRG			0x800020
# define BLU			0x0000FF
# define BRL			0xa89645
# define BRS			0x7a692b
# define BLK			0

# define CELLING		0x5c4e1f
# define FLOOR			0xb29852

// KEY
# define D 				2
# define A 				0
# define S 				1
# define W 				13
# define ESC 			53
# define RIGHT_ARROW 	123
# define LEFT_ARROW		124




typedef struct	s_ray
{
	float		side_delta_x;
	float		side_delta_y;
	float		dist;
	
	int			hit_down;
	int			hit_left;
}				t_ray;


typedef struct	s_player
{
	float		x;
	float 		y;
	float		withd;
	float		height;
	int			turn_direction; // -1 for left, 1 for right
	int			walk_direction; // î
	float		rotation_angle;
	float		walk_speed;
	float		turn_speed;
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
	
	float		img_width;
	float		img_height;
}				t_data;


typedef struct	s_texture
{
	t_data		nort;
	t_data		south;
	t_data		west;
	t_data		east;

}				t_texture;

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
	t_ray		*ray;
	t_texture	texture;
}	t_mlx;

void 	image_init(t_mlx *game);
int		move(int keycode, t_mlx *game);
void 	draw_player(t_mlx *game, int color);
bool	map_reader(char *file, t_mlx *game);
void	back_ground(t_mlx *game);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_square(t_mlx *game, int x, int y, int color);
void	draw_grid(t_mlx *game);
void	destroy_image(t_mlx *game);
void 	draw_line(t_mlx *game, float angle);
float	convert_rad_deg(float rad);
float	convert_deg_rad(float deg);
void	draw_fov(t_mlx *game);
void	dda(t_mlx *game, float angle);
float	normalize_angle(float angle);
t_ray	dda_v2(t_mlx *game, float angle);
int		get_pixel(t_data *data, int x, int y);
void	draw_walls_beta(t_mlx *game, t_ray ray, int pixel_x, float angle);
void	print_texture(t_data *img, t_data *img_texture, float stepx, float stepy, float lineO, float ty_step, float lineH, float pixel_x);
t_data	*cardinal_points(t_ray *ray, t_mlx *game);

#endif