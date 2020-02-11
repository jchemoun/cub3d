/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 02:22:01 by jchemoun          #+#    #+#             */
/*   Updated: 2020/02/11 15:45:05 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

void	line_init(t_line *line, t_cara *cara, t_win *win, int i)
{
	line->camx = (2 * i / (float)win->l) - 1;
	line->ray_dirx = cara->dirx + cara->planx * line->camx;
	line->ray_diry = cara->diry + cara->plany * line->camx;
	line->delta_distx = fabs(1 / (line->ray_dirx));
	line->delta_disty = fabs(1 / (line->ray_diry));
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

void	line_init_sprite(t_cub3d *cub, int mapx, int mapy)
{
	cub->line_spr->invdet = 1.0 / (cub->cara->planx * cub->cara->diry
		- cub->cara->dirx * cub->cara->plany);
	cub->line_spr->posx = (mapx - cub->cara->posx) + 0.5;
	cub->line_spr->posy = (mapy - cub->cara->posy) + 0.5;
	cub->line_spr->trx = cub->line_spr->invdet * (cub->cara->diry *
		cub->line_spr->posx - cub->cara->dirx * cub->line_spr->posy);
	cub->line_spr->try = cub->line_spr->invdet * (-cub->cara->plany *
		cub->line_spr->posx + cub->cara->planx * cub->line_spr->posy);
	cub->line_spr->spscx = (int)((cub->win->l / 2) *
		(1 + cub->line_spr->trx / cub->line_spr->try));
	cub->line_spr->sprheigth = (int)(abs((int)(cub->win->h /
		cub->line_spr->try)));
	cub->line_spr->drawstarty = -cub->line_spr->sprheigth / 2 + cub->win->h / 2;
	draw_sprite(cub);
}

void	ft_sort_spr(int *spr, int n_spr, t_cara *cara)
{
	int	i;
	int	j;

	i = 0;
	while (i <= n_spr)
	{
		j = 0;
		while (j <= i)
		{
			if (sqrt((*(spr + (n_spr - j) * 2) - cara->posx) * (*(spr + (n_spr -
				j) * 2) - cara->posx) + (*(spr + (n_spr - j) * 2 + 1) -
				cara->posy) * (*(spr + (n_spr - j) * 2 + 1) - cara->posy)) <
				sqrt((*(spr + (n_spr - i) * 2) - cara->posx) * (*(spr + (n_spr -
				i) * 2) - cara->posx) + (*(spr + (n_spr - i) * 2 + 1) -
				cara->posy) * (*(spr + (n_spr - i) * 2 + 1) - cara->posy)))
			{
				ft_swap((spr + (n_spr - j) * 2), spr + (n_spr - i) * 2);
				ft_swap((spr + (n_spr - j) * 2 + 1), spr + (n_spr - i) * 2 + 1);
			}
			j++;
		}
		i++;
	}
}

void	line_sprite(t_cub3d *cub)
{
	int			i;
	int			spr[10000];
	int			n_spr;
	int			j;

	i = -1;
	n_spr = 0;
	j = 0;
	while (i++ < cub->win->l)
	{
		cub->line->mapx = (int)cub->cara->posx;
		cub->line->mapy = (int)cub->cara->posy;
		line_init(cub->line, cub->cara, cub->win, i);
		cub->line->side = dda_algo_sprite(cub->line, cub->map, spr, &n_spr);
	}
	n_spr >= 2 ? ft_sort_spr(spr, n_spr, cub->cara) : 0;
	j = 1;
	while (j <= n_spr)
	{
		line_init_sprite(cub, *(spr + (n_spr - j) * 2), *(spr + ((n_spr - j)
			* 2) + 1));
		j++;
	}
}

void	line_wall(t_cub3d *cub)
{
	int	hit;
	int	i;

	i = -1;
	while (++i < cub->win->l)
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
		cub->line_spr->wallz[i] = cub->line->wall_size;
		draw_wall(cub, i);
	}
}
