/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:31:50 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:14:03 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

int			get_first_line(int fd, char **line)
{
	int ret;

	while (ft_strncmp(*line, "", 1) == 0 || check_first_char(*line, "1") != 1)
	{
		if (*line)
			free(*line);
		if ((ret = get_next_line_map(fd, line)) != 1)
		{
			free(*line);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	check_play(t_game *game, int i, int j, int *play)
{
	if (*play == 0 && (game->map.map[i][j] == 'S' - 48 ||
		game->map.map[i][j] == 'N' - 48 ||
		game->map.map[i][j] == 'W' - 48 ||
		game->map.map[i][j] == 'E' - 48))
	{
		*play = 1;
		game->y = i;
		game->x = j;
		game->face = game->map.map[i][j] + 48;
		game->map.map[i][j] = 0;
		return (1);
	}
	return (0);
}

static int	check_char(t_game *game)
{
	int i;
	int j;
	int play;

	i = -1;
	play = 0;
	while (++i < game->map.height - 1)
	{
		j = -1;
		while (++j < game->map.width - 1)
			if (game->map.map[i][j] != 1 && game->map.map[i][j] != 0 &&
			game->map.map[i][j] != 2)
				if (check_play(game, i, j, &play) == 0)
					return (EXIT_FAILURE);
	}
	if (play == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_wall(t_map map)
{
	int i;

	i = -1;
	while (++i < map.width - 1)
		if (map.map[0][i] != 1 || map.map[map.height - 2][i] != 1)
			return (EXIT_FAILURE);
	i = -1;
	while (++i < map.height - 1)
		if (!(map.map[i][0] == 1 && map.map[i][map.width - 2] == 1))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			check_map(t_game *game)
{
	if (game->map.height < 3 || game->map.width < 3)
		return (EXIT_FAILURE);
	if (check_wall(game->map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_char(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
