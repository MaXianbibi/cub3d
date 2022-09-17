/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 02:37:39 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/17 03:53:44 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_fov(t_mlx *game)
{
	float i;
	float cangle = game->player.rotation_angle;
	
		// printf("%f\n", convert_rad_deg(cangle));
	i =	convert_rad_deg(cangle);
	float j = i + 66.0;
	while (i < j)
	{
		cangle = convert_deg_rad(i - 33.0);
		draw_line(game, cangle);
		i += 0.25;
	}
	draw_line_dda(game, game->player.rotation_angle);
}

void draw_line(t_mlx *game, float angle)
{
	// int i = 0;
	float px = game->player.x;
	float py = game->player.y;

	while (game->map.map[(int)(py / 64)][(int)(px / 64)] != '1')
	{
		my_mlx_pixel_put(&game->img, px, py, GRN);	
		px += cos(angle);
		py -= sin(angle);
	}
}

void draw_line_dda(t_mlx *game, float angle)
{
	float side_dist_x = 0;
	float side_dist_y = 0;
	float ray_dir_x = cos(angle);
	float ray_dir_y = sin(angle);
	
	float deltaDistX = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
	float deltaDistY = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
	// int hit = 0;
	
		printf("%f, %f\n", deltaDistX, deltaDistY);
// 	int mapX = (int)game->player.x;
// 	int mapY = (int)game->player.y;
// 	int stepX = 0;
// 	int stepY = 0;
	
// 	int side;


// 	if (ray_dir_x < 0)
// 	{
// 		side_dist_x = ((int)game->player.x - game->player.x) * deltaDistX;
// 		stepX = -1;
// 	}
// 	else
// 	{
// 		side_dist_x = (game->player.x + 1.0 - (int)game->player.x) * deltaDistX;
// 		stepX = 1;
// 	}
// 	if (ray_dir_y < 0)
// 	{
// 		side_dist_y = ((int)game->player.y - game->player.y) * deltaDistY;
// 		stepY = -1;	
// 	}
// 	else
// 	{
// 		side_dist_y = (game->player.y + 1.0 - (int)game->player.y) * deltaDistY;
// 		stepY = 1;	
// 	}

// 	while (hit == 0)
//       {
//         //jump to next map square, either in x-direction, or in y-direction
//         if (side_dist_x < side_dist_y)
//         {
//           side_dist_x += deltaDistX;
//           mapX += stepX;
//           side = 0;
//         }
//         else
//         {
//           side_dist_y += deltaDistY;
//           mapY += stepY;
//           side = 1;
//         }
//         //Check if ray has hit a wall
//         if (game->map.map[(int)mapX / 64][(int)mapY / 64] > 0) hit = 1;
//       } 
	
// // 
		my_mlx_pixel_put(&game->img, side_dist_x, side_dist_y, RED);	
// 

}