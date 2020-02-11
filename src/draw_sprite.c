/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:53:34 by jchemoun          #+#    #+#             */
/*   Updated: 2020/02/11 15:32:20 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

/*
** void	draw_spr(t_cub3d *cub, int i, int texx, int texy)
** {
**	t_img	*tex;
**
**	tex = cub->entry->sprite1;
**	if ((unsigned int)*(tex->img_addr + (texx * 4 + 0) + (tex->size_line *
**	texy)) != (unsigned int)152 && (unsigned int)*(tex->img_addr + (texx *
**	4 + 1) + (tex->size_line * texy)) != (unsigned int)0 && (unsigned int)*
**	(tex->img_addr + (texx * 4 + 2) + (tex->size_line * texy)) !=
**	(unsigned int)136)
**	{
**		*(cub->img->img_addr + (i * 4 + 0) + (cub->img->size_line * cub->line
**		->start)) = *(tex->img_addr + (texx * 4 + 0) + (tex->size_line * texy));
**		*(cub->img->img_addr + (i * 4 + 1) + (cub->img->size_line * cub->line
**		->start)) = *(tex->img_addr + (texx * 4 + 1) + (tex->size_line * texy));
**		*(cub->img->img_addr + (i * 4 + 2) + (cub->img->size_line * cub->line
**		->start)) = *(tex->img_addr + (texx * 4 + 2) + (tex->size_line * texy));
**		*(cub->img->img_addr + (i * 4 + 3) + (cub->img->size_line * cub->
**		line->start)) = *(tex->img_addr + (texx * 4 + 3) + (tex->
**		size_line * texy));
**	}
** }
** void	draw_sprite(t_cub3d *cub, int i)
** {
**	int		texx;
**	int		texy;
**	t_img	*tex;
**
**	tex = cub->entry->sprite1;
**	if (cub->line->side == 1)
**		cub->line->wall_hit = cub->cara->posy + (float)
**		(cub->line->wall_size * cub->line->ray_diry);
**	else
**		cub->line->wall_hit = (cub->line->wall_size * cub->line->
**		ray_dirx) + cub->cara->posx;
**	cub->line->wall_hit -= floor(cub->line->wall_hit);
**	texx = ((int)(cub->line->wall_hit * (float)tex->width));
**	if (cub->line->side == 1 && cub->line->ray_dirx > 0)
**		texx = tex->width - texx - 1;
**	if (cub->line->side == 0 && cub->line->ray_diry < 0)
**		texx = tex->width - texx - 1;
**	while (cub->line->start < cub->line->end)
**	{
**		texy = ((((cub->line->start * 256) - (cub->win->h * 128) +
**		(cub->line->lineh * 128)) * tex->height) / cub->line->lineh) / 256;
**		draw_spr(cub, i, texx, texy);
**		cub->line->start++;
**	}
** }
*/

void	draw_spr(t_cub3d *cub, int jk[2], int tex[2])
{
	t_img	*texi;

	texi = cub->entry->sprite1;
	*(cub->img->img_addr + ((jk[0]) * 4 + 0) + (cub->img->size_line *
		(jk[1]))) = *(texi->img_addr + (tex[0] * 4 + 0) +
		(texi->size_line * tex[1]));
	*(cub->img->img_addr + ((jk[0]) * 4 + 1) + (cub->img->size_line *
		(jk[1]))) = *(texi->img_addr + (tex[0] * 4 + 1) +
		(texi->size_line * tex[1]));
	*(cub->img->img_addr + ((jk[0]) * 4 + 2) + (cub->img->size_line *
		(jk[1]))) = *(texi->img_addr + (tex[0] * 4 + 2) +
		(texi->size_line * tex[1]));
	*(cub->img->img_addr + ((jk[0]) * 4 + 3) + (cub->img->size_line *
		(jk[1]))) = *(texi->img_addr + (tex[0] * 4 + 3) +
		(texi->size_line * tex[1]));
}

void	draw_spri(t_cub3d *cub, int jk[2], int drawendy, int texx)
{
	t_img	*tex;
	int		d;
	int		texy;

	tex = cub->entry->sprite1;
	while (jk[1] < drawendy)
	{
		d = (jk[1]) * 256 - cub->win->h * 128 + cub->line_spr->sprheigth * 128;
		texy = ((d * tex->height) / cub->line_spr->sprheigth) / 256;
		if (((unsigned int)*(tex->img_addr + (texx * 4 + 0) + (tex->size_line *
			texy)) != (unsigned int)152 && (unsigned int)*(tex->img_addr +
			(texx * 4 + 1) + (tex->size_line * texy)) != (unsigned int)0 &&
			(unsigned int)*(tex->img_addr + (texx * 4 + 2) + (tex->size_line *
			texy)) != (unsigned int)136))
		{
			draw_spr(cub, jk, ((int[2]){texx, texy}));
		}
		jk[1]++;
	}
}

void	drwaw_sprit(t_cub3d *cub, int drawendx, int drawendy)
{
	t_img	*tex;
	int		j;
	int		k;
	int		texx;

	tex = cub->entry->sprite1;
	j = cub->line_spr->drawstartx;
	k = cub->line_spr->drawstarty;
	while (j < drawendx)
	{
		texx = (int)(((256 * (((j)) - (-cub->line_spr->sprwidth / 2 +
			cub->line_spr->spscx)) * tex->width / cub->line_spr->sprwidth)
			/ 256));
		k = cub->line_spr->drawstarty;
		if (cub->line_spr->try > 0 && j > 0 && j < cub->win->l &&
			cub->line_spr->try < cub->line_spr->wallz[j])
			draw_spri(cub, ((int[2]){j, k}), drawendy, texx);
		j++;
	}
}

void	draw_sprite(t_cub3d *cub)
{
	int	drawendy;
	int drawendx;

	if (cub->line_spr->drawstarty < 0)
		cub->line_spr->drawstarty = 0;
	drawendy = cub->line_spr->sprheigth / 2 + cub->win->h / 2;
	if (drawendy >= cub->win->h)
		drawendy = cub->win->h - 1;
	cub->line_spr->sprwidth = (int)(abs((int)(cub->win->h /
		cub->line_spr->try)));
	cub->line_spr->drawstartx = -cub->line_spr->sprwidth /
		2 + cub->line_spr->spscx;
	if (cub->line_spr->drawstartx < 0)
		cub->line_spr->drawstartx = 0;
	drawendx = cub->line_spr->sprwidth / 2 + cub->line_spr->spscx;
	if (drawendx >= cub->win->l)
		drawendx = cub->win->l - 1;
	drwaw_sprit(cub, drawendx, drawendy);
}
