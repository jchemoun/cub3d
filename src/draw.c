/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 02:29:01 by jchemoun          #+#    #+#             */
/*   Updated: 2020/02/06 17:09:44 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

void	draw_tex(t_cub3d *cub, t_img *tex, int i)
{
	int texy;
	int texx;

	texx = ((int)(cub->line->wall_hit * (float)tex->width));
	if (cub->line->side == 1 && cub->line->ray_dirx > 0)
		texx = tex->width - texx - 1;
	if (cub->line->side == 0 && cub->line->ray_diry < 0)
		texx = tex->width - texx - 1;
	while (cub->line->start < cub->line->end)
	{
		texy = ((((cub->line->start * 256) - (cub->win->h * 128) +
		(cub->line->lineh * 128)) * tex->height) / cub->line->lineh) / 256;
		*(cub->img->img_addr + (i * 4 + 0) + (cub->img->size_line *
		cub->line->start)) = *(tex->img_addr + (texx * 4 + 0) +
		(tex->size_line * texy));
		*(cub->img->img_addr + (i * 4 + 1) + (cub->img->size_line *
		cub->line->start)) = *(tex->img_addr + (texx * 4 + 1) +
		(tex->size_line * texy));
		*(cub->img->img_addr + (i * 4 + 2) + (cub->img->size_line *
		cub->line->start)) = *(tex->img_addr + (texx * 4 + 2) +
		(tex->size_line * texy));
		*(cub->img->img_addr + (i * 4 + 3) + (cub->img->size_line *
		cub->line->start++)) = *(tex->img_addr + (texx * 4 + 3) +
		(tex->size_line * texy));
	}
}

void	draw_font(t_img *img, t_win *win, t_entry *entry)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < win->h)
	{
		j = 0;
		while (j < win->l)
		{
			*(img->img_addr + (j * 4 + 0) + (img->size_line * i)) =
				(i < win->h / 2) ? (unsigned)entry->f_r : (unsigned)entry->c_r;
			*(img->img_addr + (j * 4 + 1) + (img->size_line * i)) =
				(i < win->h / 2) ? (unsigned)entry->f_g : (unsigned)entry->c_g;
			*(img->img_addr + (j * 4 + 2) + (img->size_line * i)) =
				(i < win->h / 2) ? (unsigned)entry->f_b : (unsigned)entry->c_b;
			j++;
		}
		i++;
	}
}

void	draw_wall(t_cub3d *cub, int i)
{
	if (cub->line->side == 1)
		cub->line->wall_hit = cub->cara->posy +
		(float)(cub->line->wall_size * cub->line->ray_diry);
	else
		cub->line->wall_hit = (cub->line->wall_size * cub->line->ray_dirx)
		+ cub->cara->posx;
	cub->line->wall_hit -= floor(cub->line->wall_hit);
	if (cub->line->side == 1)
	{
		if (cub->line->wall_size * cub->line->ray_dirx > 0)
			draw_tex(cub, cub->entry->no_tex, i);
		else
			draw_tex(cub, cub->entry->so_tex, i);
	}
	else if (cub->line->side == 0)
	{
		if (cub->line->wall_size * cub->line->ray_diry > 0)
			draw_tex(cub, cub->entry->we_tex, i);
		else
			draw_tex(cub, cub->entry->ea_tex, i);
	}
}
