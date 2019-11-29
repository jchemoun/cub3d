/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 03:34:25 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:25:27 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

static char	*parse_wall_n(int fd, char *side)
{
	int		ret;
	char	**res;
	char	*line;

	res = NULL;
	line = ft_strdup("");
	while (ft_strncmp(line, "", 1) == 0 && check_first_char(line, side) != 1)
		if ((ret = get_next_line(fd, &line, side)) != 1)
		{
			free_parse(line, (void**)res);
			return (NULL);
		}
	if ((res = ft_split(line, ' ')) == NULL || res[2] != 0 ||
		ft_strncmp(res[0], side, ft_strlen(res[0])))
	{
		free_parse(line, (void**)res);
		return (NULL);
	}
	free(line);
	free(res[0]);
	free(res);
	return (res[1]);
}

int			parse_wall(t_game *game, char *path)
{
	int	fd;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	if ((game->texture.north_text = parse_wall_n(fd, "NO")) == NULL)
		return (EXIT_FAILURE);
	close(fd);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	if ((game->texture.south_text = parse_wall_n(fd, "SO")) == NULL)
		return (EXIT_FAILURE);
	close(fd);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	if ((game->texture.west_text = parse_wall_n(fd, "WE")) == NULL)
		return (EXIT_FAILURE);
	close(fd);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	if ((game->texture.east_text = parse_wall_n(fd, "EA")) == NULL)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}
