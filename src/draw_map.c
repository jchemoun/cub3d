/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 05:32:07 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:07:13 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

t_color	ret(t_color col, int r, int g, int b)
{
	col.red = r;
	col.green = g;
	col.blue = b;
	return (col);
}

t_color	is_wall(t_cub3d *cub, int i, int j)
{
	int		y;
	int		x;
	t_color col;

	col.blue = 0;
	y = (i - 0) * (cub->map.height - 0) / ((cub->win->h / 4) - 0) + 0;
	x = (j - 0) * (cub->map.width - 0) / ((cub->win->l / 6) - 0) + 0;
	col = ret(col, 1, 25, 25);
	if (y >= cub->map.height || x >= cub->map.width)
		return (col);
	if (cub->map.map[y][x] == 1)
		col = ret(col, 25, 25, 25);
	else if (cub->map.map[y][x] == 0)
		col = ret(col, 180, 180, 180);
	else if (cub->map.map[y][x] == 2)
		col = ret(col, 180, 30, 30);
	if (x == (int)cub->cara->posy && y == (int)cub->cara->posx)
		col = ret(col, 30, 180, 30);
	return (col);
}

void	draw_map(t_img *img, t_win *win, t_cub3d *cub)
{
	int		i;
	int		j;
	t_color	col;

	i = 0;
	j = 0;
	while (i < win->h / 4)
	{
		j = 0;
		while (j < win->l / 6)
		{
			col = is_wall(cub, i, j);
			if (col.red == 1)
				break ;
			*(img->img_addr + (j * 4 + 0) + (img->size_line * i)) =
			(unsigned)col.red;
			*(img->img_addr + (j * 4 + 1) + (img->size_line * i)) =
			(unsigned)col.green;
			*(img->img_addr + (j * 4 + 2) + (img->size_line * i)) =
			(unsigned)col.blue;
			j++;
		}
		i++;
	}
}
