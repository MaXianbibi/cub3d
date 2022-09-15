/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 03:07:05 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/15 03:22:51 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	file_linecount(char *file)
{
	int		linecount;
	int		fd;
	int		readcount;
	char	c;

	fd = open(file, O_RDONLY);
	if (!fd)
		return (-1);
	linecount = 1;
	while (1)
	{
		readcount = read(fd, &c, 1);
		if (readcount < 0 || (readcount == 0 && linecount == 1))
			return (-1);
		if (readcount == 0)
			break ;
		if (c == '\n')
			linecount++;
	}
	close(fd);
	return (linecount);
}

bool	map_reader(char *file, t_mlx *game)
{
	int	fd;
	int	i;
	int	col;

	i = 0;
	game->map.col = file_linecount(file);
	col = game->map.col;
	if (col == -1)
		return (ft_print_error("La map est vide ou incomplete\n"));
	game->map.map = malloc(sizeof(char *) * game->map.col + 1);
	fd = open(file, O_RDONLY);
	while (i < col)
	{	
		game->map.map[i] = get_next_line(fd);
		if (game->map.map[i] == NULL || game->map.map[i][0] == '\n')
			game->map.col--;
		i++;
	}
	i = 0;
	while (game->map.map[0][++i])
		game->map.raw++;
	game->map.map[col] = NULL;
	return (0);
}
