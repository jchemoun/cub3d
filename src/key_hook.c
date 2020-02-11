/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 02:17:31 by jchemoun          #+#    #+#             */
/*   Updated: 2020/02/04 10:08:24 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

int		key_release_hook(int key, t_win *win)
{
	if (key == 0)
		win->a = 0;
	else if (key == 1)
		win->s = 0;
	else if (key == 2)
		win->d = 0;
	else if (key == 13)
		win->w = 0;
	else if (key == 123)
		win->lar = 0;
	else if (key == 124)
		win->rar = 0;
	return (0);
}

int		key_press_hook(int key, t_win *win)
{
	if (key == 53)
		exit(1);
	else if (key == 0)
		win->a = 1;
	else if (key == 1)
		win->s = 1;
	else if (key == 2)
		win->d = 1;
	else if (key == 13)
		win->w = 1;
	else if (key == 123)
		win->lar = 1;
	else if (key == 124)
		win->rar = 1;
	return (0);
}

void	hook_init(t_cub3d *cub)
{
	mlx_do_key_autorepeatoff(cub->win->mlx);
	mlx_hook(cub->win->win, 2, 0, key_press_hook, cub->win);
	mlx_hook(cub->win->win, 3, 0, key_release_hook, cub->win);
	mlx_hook(cub->win->win, 17, 0, exit_prog, cub);
}

int		loop_hook(t_cub3d *cub)
{
	if (cub->win->w == 1)
		move_front(cub->cara, cub->map);
	if (cub->win->s == 1)
		move_back(cub->cara, cub->map);
	if (cub->win->a == 1)
		move_left(cub->cara, cub->map);
	if (cub->win->d == 1)
		move_right(cub->cara, cub->map);
	if (cub->win->rar == 1)
		rotate_right(cub->cara);
	if (cub->win->lar == 1)
		rotate_left(cub->cara);
	draw_font(cub->img, cub->win, cub->entry);
	line_wall(cub);
	line_sprite(cub);
	draw_map(cub->img, cub->win, cub);
	if (cub->win->win == NULL || cub->win->mlx == NULL ||
		cub->win->bmp)
		save_bmp(cub);
	mlx_put_image_to_window(cub->win->mlx, cub->win->win,
	cub->img->img_ptr, 0, 0);
	return (1);
}
