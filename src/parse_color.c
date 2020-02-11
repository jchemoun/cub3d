/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 04:14:34 by jchemoun          #+#    #+#             */
/*   Updated: 2020/02/04 12:43:36 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

static char	**ft_parse_color(char *tmp)
{
	char **res;

	if ((res = ft_split(tmp, ',')) == NULL)
	{
		free(tmp);
		return (NULL);
	}
	if (res[3] != 0 || len_digit(res[0]) == 0 || len_digit(res[1]) == 0 ||
		len_digit(res[2]) == 0)
	{
		free(tmp);
		ft_free_tab((void**)res);
		return (NULL);
	}
	free(tmp);
	return (res);
}

static char	*parse_color_n(int fd, char *side)
{
	int		ret;
	char	**res;
	char	*line;

	res = NULL;
	line = ft_strdup("");
	while (ft_strncmp(line, "", 1) == 0 && check_first_char(line, side) != 1)
	{
		if ((ret = get_next_line(fd, &line, side)) != 1)
		{
			free_parse(line, (void**)res);
			return (NULL);
		}
	}
	if ((res = ft_split(line, ' ')) == NULL ||
		res[2] != 0 || ft_strncmp(res[0], side, ft_strlen(res[0])))
	{
		free_parse(line, (void**)res);
		return (NULL);
	}
	free(line);
	free(res[0]);
	return (res[1]);
}

static char	**parse_col(int fd, char *side)
{
	char	**res;
	char	*tmp;

	tmp = NULL;
	if ((tmp = parse_color_n(fd, side)) == NULL)
		return (NULL);
	if ((res = ft_parse_color(tmp)) == NULL)
	{
		ft_free_tab((void**)res);
		return (NULL);
	}
	return (res);
}

t_color		fill_color(t_color color, char **tmp)
{
	color.red = ft_atoi(tmp[0]);
	color.blue = ft_atoi(tmp[1]);
	color.green = ft_atoi(tmp[2]);
	ft_free_tab((void**)tmp);
	return (color);
}

int			parse_color(t_game *game, char *path)
{
	int		fd;
	char	**tmp;
	t_color floor;
	t_color	roof;

	floor.blue = 0;
	roof.blue = 0;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	if ((tmp = parse_col(fd, "F")) == NULL)
		return (EXIT_FAILURE);
	close(fd);
	game->texture.floor = fill_color(floor, tmp);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	if ((tmp = parse_col(fd, "C")) == NULL)
		return (EXIT_FAILURE);
	close(fd);
	game->texture.roof = fill_color(roof, tmp);
	return (EXIT_SUCCESS);
}
