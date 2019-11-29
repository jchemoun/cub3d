/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 01:48:34 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:25:32 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

int			check_first_char(char *line, char *wich)
{
	char *tmp;

	tmp = line;
	if ((line = ft_strtrim(line, " ")) == NULL)
		return (0);
	if (strncmp("S", wich, 2) == 0)
	{
		if (strncmp(line, wich, ft_strlen(wich)) == 0 &&
			strncmp(line, "SO", 2) != 0)
		{
			free(line);
			return (1);
		}
		free(line);
		return (0);
	}
	if (strncmp(line, wich, ft_strlen(wich)) == 0)
	{
		free(line);
		return (1);
	}
	free(line);
	return (0);
}

int			parse_res(t_game *game, int fd)
{
	int		ret;
	char	**res;
	char	*line;

	res = NULL;
	line = ft_strdup("");
	while (ft_strncmp(line, "", 1) == 0 && check_first_char(line, "R") != 1)
		if ((ret = get_next_line(fd, &line, "R")) != 1)
			return (free_parse(line, (void**)res));
	if ((res = ft_split(line, ' ')) == NULL)
		return (free_parse(line, (void**)res));
	if (res[3] != 0 || ft_strncmp(res[0], "R", ft_strlen(res[0])) ||
		!len_digit(res[1]) || !len_digit(res[2]))
		return (free_parse(line, (void**)res));
	game->win.height = ft_atoi(res[1]);
	game->win.width = ft_atoi(res[2]);
	if (game->win.height <= 0 || game->win.width <= 0)
		return (free_parse(line, (void**)res));
	if (game->win.height > 2560 || game->win.width > 1440)
	{
		game->win.height = 2560;
		game->win.width = 1440;
	}
	free_parse(line, (void**)res);
	return (EXIT_SUCCESS);
}

int			parse_sprite(t_game *game, int fd)
{
	int		ret;
	char	**res;
	char	*line;

	res = NULL;
	line = ft_strdup("");
	while (ft_strncmp(line, "", 1) == 0 && check_first_char(line, "S") != 1)
		if ((ret = get_next_line(fd, &line, "S")) != 1)
			return (free_parse(line, (void**)res));
	if ((res = ft_split(line, ' ')) == NULL)
		return (free_parse(line, (void**)res));
	if (res[2] != 0 || ft_strncmp(res[0], "S", ft_strlen(res[0])))
		return (free_parse(line, (void**)res));
	free(line);
	free(res[0]);
	free(res);
	game->texture.wall_text = res[1];
	return (EXIT_SUCCESS);
}

int			parse_file(t_game *game, char *path)
{
	int fd;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	if (parse_res(game, fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close(fd);
	if (parse_wall(game, path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	if (parse_sprite(game, fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close(fd);
	if (parse_color(game, path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_map(game, path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
