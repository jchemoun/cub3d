/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 02:03:31 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:25:20 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

int		**add_first_line(int **map, char *path)
{
	int		i;
	int		fd;
	char	**tmp;
	char	*line;

	i = -1;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	line = ft_strdup("");
	if ((get_first_line(fd, &line)) == EXIT_FAILURE)
		return (NULL);
	close(fd);
	if ((tmp = ft_split(line, ' ')) == NULL)
		return (NULL);
	free(line);
	if ((map[0] = (int*)malloc(sizeof(int) * (str_strlen(tmp) + 1))) == NULL)
		return (NULL);
	while (++i < (int)str_strlen(tmp))
		map[0][i] = tmp[i][0] - 48;
	ft_free_tab((void**)tmp);
	return (map);
}

int		get_len(char *path)
{
	int		fd;
	int		ret;
	int		size;
	char	*line;

	size = 0;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	line = ft_strdup("");
	if ((get_first_line(fd, &line)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	size++;
	while (check_first_char(line, "1") == 1)
	{
		if (line)
			free(line);
		if ((ret = get_next_line_map(fd, &line)) != 1)
		{
			free(line);
			return (EXIT_FAILURE);
		}
		size++;
	}
	close(fd);
	return (size);
}

int		**map_filler(int **tab, char *line, int size)
{
	int		i;
	int		len;
	char	**tmp;

	i = -1;
	if (tab == NULL || line == NULL)
		return (NULL);
	if ((tmp = ft_split(line, ' ')) == NULL)
		return (NULL);
	len = str_strlen(tmp);
	if ((tab[size - 1] = (int*)malloc(sizeof(int) * (len + 1))) == NULL)
		return (NULL);
	while (++i < len)
		tab[size - 1][i] = (int)(tmp[i][0] - 48);
	ft_free_tab((void**)tmp);
	return (tab);
}

int		**read_all(int **map, int fd, int *size)
{
	int		ret;
	char	*line;

	ret = 1;
	line = ft_strdup("1");
	while (ret == 1 && check_first_char(line, "1") == 1)
	{
		if ((ret = get_next_line_map(fd, &line)) == -1)
		{
			free_parse(line, (void**)map);
			return (NULL);
		}
		*size = *size + 1;
		if ((map = map_filler(map, line, *size)) == NULL)
			return (NULL);
	}
	if (line)
		free(line);
	return (map);
}

int		parse_map(t_game *game, char *path)
{
	int		fd;
	int		ret;
	int		size;
	char	*line;
	int		**map;

	map = NULL;
	ret = 1;
	size = get_len(path);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	line = ft_strdup("");
	if ((get_first_line(fd, &line)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((map = (int**)malloc(sizeof(int*) * (size + 1))) == NULL)
		return (EXIT_FAILURE);
	map[size] = 0;
	size = 1;
	if ((map = read_all(map, fd, &size)) == NULL)
		return (EXIT_FAILURE);
	close(fd);
	game->map.map = add_first_line(map, path);
	game->map.height = size;
	game->map.width = 30;
	return (EXIT_SUCCESS);
}
