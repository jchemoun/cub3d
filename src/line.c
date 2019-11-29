/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 02:22:01 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:07:13 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

void	line_init(t_line *line, t_cara *cara, t_win *win, int i)
{
	line->camx = (2 * i / (double)win->l) - 1;
	line->ray_dirx = cara->dirx + cara->planx * line->camx;
	line->ray_diry = cara->diry + cara->plany * line->camx;
	line->delta_distx = fabs(1 / line->ray_dirx);
	line->delta_disty = fabs(1 / line->ray_diry);
	if (line->ray_dirx < 0)
	{
		line->stepx = -1;
		line->side_distx = (cara->posx - line->mapx) * line->delta_distx;
	}
	else
	{
		line->stepx = 1;
		line->side_distx = (line->mapx + 1.0 - cara->posx) * line->delta_distx;
	}
	if (line->ray_diry < 0)
	{
		line->stepy = -1;
		line->side_disty = (cara->posy - line->mapy) * line->delta_disty;
	}
	else
	{
		line->stepy = 1;
		line->side_disty = (line->mapy + 1.0 - cara->posy) * line->delta_disty;
	}
}

void	line_sprite(t_cub3d *cub)
{
	int hit;
	int i;

	i = -1;
	while (++i < cub->win->l)
	{
		hit = 0;
		cub->line->mapx = (int)cub->cara->posx;
		cub->line->mapy = (int)cub->cara->posy;
		line_init(cub->line, cub->cara, cub->win, i);
		if ((cub->line->side = dda_algo_sprite(cub->line, cub->map) == 0))
			cub->line->wall_size = (cub->line->mapx - cub->cara->posx +
				(1 - cub->line->stepx) / 2) / cub->line->ray_dirx;
		else
			cub->line->wall_size = (cub->line->mapy - cub->cara->posy +
				(1 - cub->line->stepy) / 2) / cub->line->ray_diry;
		cub->line->lineh = (int)(cub->win->h / cub->line->wall_size);
		if ((cub->line->start = -cub->line->lineh / 2 + cub->win->h / 2) < 0)
			cub->line->start = 0;
		if ((cub->line->end = (cub->line->lineh / 2) + (cub->win->h / 2))
			>= cub->win->h)
			cub->line->end = cub->win->h;
		cub->map.map[cub->line->mapx][cub->line->mapy] > 1 ?
		draw_sprite(cub, i) : 0;
	}
}

void	line_wall(t_cub3d *cub)
{
	int hit;
	int i;

	i = 0;
	while (i < cub->win->l)
	{
		hit = 0;
		cub->line->mapx = (int)cub->cara->posx;
		cub->line->mapy = (int)cub->cara->posy;
		line_init(cub->line, cub->cara, cub->win, i);
		if ((cub->line->side = dda_algo(cub->line, cub->map) == 0))
			cub->line->wall_size = (cub->line->mapx - cub->cara->posx +
				(1 - cub->line->stepx) / 2) / cub->line->ray_dirx;
		else
			cub->line->wall_size = (cub->line->mapy - cub->cara->posy +
				(1 - cub->line->stepy) / 2) / cub->line->ray_diry;
		cub->line->lineh = (int)(cub->win->h / cub->line->wall_size);
		if ((cub->line->start = -cub->line->lineh / 2 + cub->win->h / 2) < 0)
			cub->line->start = 0;
		if ((cub->line->end = (cub->line->lineh / 2) + (cub->win->h / 2))
			>= cub->win->h)
			cub->line->end = cub->win->h;
		draw_wall(cub, i);
		i++;
	}
}
