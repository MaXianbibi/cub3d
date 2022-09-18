/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 23:24:54 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/18 02:14:52 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 02:12:49 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/18 02:12:50 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int main()
// {

// 	int angle = normalize_angle(angle);
	
// 	int is_facing_down = angle > 0 && angle < PI;
// 	int is_facing_up = !is_facing_down;
	
// 	int is_facing_right = angle < 0.5 * PI || angle > 1.5 * PI;
// 	int is_facing_left = !is_facing_right;

// 	float xintercept;
// 	float yintercept;
	
// 	float xstep;
// 	float ystep;
	
// 	int hit = 0;
	
// 	float horz_wall_hitx = 0;
// 	float horz_wall_hity = 0;
// 	// int		horz_wall_content = 0;

	
// 	yintercept = floor(game->player.y / 64) * 64;
// 	if (is_facing_down)
// 		yintercept += 64;
		
// 	xintercept = game->player.x + (yintercept - game->player.y) / tan(angle);
	
// 	ystep = 64;
// 	if (is_facing_up)
// 		ystep *= -1;
		
// 	xstep = 64 / tan(angle);
// 	if (is_facing_left && xstep > 0)
// 		xstep *= -1;
// 	if (is_facing_right && xstep < 0)
// 		xstep *= -1;
		
// 	float next_horz_touch_x = xintercept;
// 	float next_horz_touch_y = yintercept;
	
// 	while (next_horz_touch_x >= 0 && next_horz_touch_x <= WIDTH && next_horz_touch_y >= 0 && next_horz_touch_y <= HEIGHT)
// 	{
// 		float x_to_check = next_horz_touch_x;
// 		float y_to_check = next_horz_touch_x + (is_facing_up ? -1 : 0);
		
// 		if(mapHasWallAt(game, x_to_check, y_to_check))
// 		{
// 			horz_wall_hitx = next_horz_touch_x;
// 			horz_wall_hity = next_horz_touch_y;
// 			hit = 0;
// 			break;
// 		}
// 		else
// 		{
// 			next_horz_touch_x += xstep;
// 			next_horz_touch_y += ystep;
// 		}
// 	}
// }