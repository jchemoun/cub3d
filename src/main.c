/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 22:17:28 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:11:14 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

void			ft_free_tab(void **tab)
{
	int i;

	i = -1;
	while (tab != NULL && tab[++i])
		free(tab[i]);
	if (tab)
		free(tab);
}

static t_game	*parse_input(t_game *game, char *av[], int ac)
{
	char	**tmp;

	if ((tmp = ft_split(av[1], '.')) == NULL)
		return (NULL);
	if (tmp[2] != 0)
		return (NULL);
	if (strncmp(tmp[1], "cub", 4) != 0)
	{
		ft_free_tab((void**)tmp);
		return (NULL);
	}
	ft_free_tab((void**)tmp);
	if (ac == 3)
	{
		if (strncmp(av[2], "--save", 7) != 0)
			return (NULL);
		game->win.bmp = 1;
	}
	else
		game->win.bmp = 0;
	return (game);
}

static int		ft_print_error(t_game *game, char *text)
{
	if (game)
	{
		if (game->map.map)
			ft_free_tab((void**)game->map.map);
		if (game->texture.north_text)
			free(game->texture.north_text);
		if (game->texture.south_text)
			free(game->texture.south_text);
		if (game->texture.east_text)
			free(game->texture.east_text);
		if (game->texture.west_text)
			free(game->texture.west_text);
		if (game->texture.wall_text)
			free(game->texture.wall_text);
		free(game);
	}
	ft_printf("Error\n%s\n", text);
	return (EXIT_FAILURE);
}

static t_game	*init_param(t_game *game, char *av[], int ac)
{
	if ((game = (t_game*)malloc(sizeof(t_game))) == NULL)
		return (NULL);
	if ((game = parse_input(game, av, ac)) == NULL)
		return (NULL);
	if (parse_file(game, av[1]) == EXIT_FAILURE)
		return (NULL);
	if (check_map(game) == EXIT_FAILURE)
		return (NULL);
	return (game);
}

int				main(int ac, char *av[])
{
	t_game	*game;

	game = NULL;
	if (ac != 2 && ac != 3)
		return (ft_print_error(game, "Usage -- Cub3d [file].cub [-save]"));
	if ((game = init_param(game, av, ac)) == NULL)
		return (ft_print_error(game, "Map error"));
	if (ray(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
