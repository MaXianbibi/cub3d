/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 00:58:59 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/21 01:47:13 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_walls(t_mlx *game, float disT, int pixel_x, float angle)
{
	
	// float ca =  normalize_angle(game->player.rotation_angle) - normalize_angle(angle);
	// if (ca < 0)
	// 	ca += 2*PI;
	// if (ca > 2 * PI)
	// 	ca -= 2*PI;
		
	// disT = disT * cos(ca);
	float lineH = (32 * HEIGHT) / disT;
	if (lineH > HEIGHT)
		lineH = HEIGHT;
	int i;
	float lineO = (HEIGHT / 2) - lineH/2;
	i = 0;

	while (i < lineH)
	{
		my_mlx_pixel_put(&game->img, pixel_x + WIDTH, i + lineO, RED);
		i++;
	}
}