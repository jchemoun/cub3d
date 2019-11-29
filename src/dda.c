/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 02:26:50 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:07:13 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

int		dda_algo(t_line *line, t_map map)
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

int		dda_algo_sprite(t_line *line, t_map map)
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
		hit = map.map[line->mapx][line->mapy];
	}
	return (side);
}
