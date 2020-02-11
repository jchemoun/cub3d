/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 02:26:50 by jchemoun          #+#    #+#             */
/*   Updated: 2020/02/11 15:12:39 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

int					dda_algo(t_line *line, t_map map)
{
	int hit;
	int side;

	hit = 0;
	while (!hit)
	{
		if (line->side_distx < line->side_disty)
		{
			line->side_distx += line->delta_distx;
			line->mapx += line->stepx;
			side = 0;
		}
		else
		{
			line->side_disty += line->delta_disty;
			line->mapy += line->stepy;
			side = 1;
		}
		hit = map.map[line->mapx][line->mapy] == 1 ? 1 : 0;
	}
	return (side);
}

static inline void	line_dda(t_line *line)
{
	if (line->side_distx < line->side_disty)
	{
		line->side_distx += line->delta_distx;
		line->mapx += line->stepx;
	}
	else
	{
		line->side_disty += line->delta_disty;
		line->mapy += line->stepy;
	}
}

int					check_spr(int mapx, int mapy, int *spr, int *n_spr)
{
	int	i;

	i = *n_spr;
	while (i > 0)
	{
		if ((*(spr + (*n_spr - i) * 2) == mapx &&
			*(spr + (*n_spr - i) * 2 + 1) == mapy))
			return (0);
		i--;
	}
	return (1);
}

int					dda_algo_sprite(t_line *line, t_map map, int *spr,
						int *n_spr)
{
	int hit;
	int side;

	hit = 0;
	side = 1;
	while (!hit)
	{
		line_dda(line);
		if ((map.map[line->mapx][line->mapy]) == 2 &&
			check_spr(line->mapx, line->mapy, spr, n_spr))
		{
			*(spr + (*n_spr * 2)) = line->mapx;
			*(spr + (*n_spr * 2) + 1) = line->mapy;
			*(n_spr) = *(n_spr) + 1;
		}
		hit = (map.map[line->mapx][line->mapy] == 1);
	}
	return (side);
}
