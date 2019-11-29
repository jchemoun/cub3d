/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:55:18 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:07:13 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

void	destroy_win(t_win *win)
{
	mlx_destroy_window(win->mlx, win->win);
	free(win);
}

int		exit_prog(int key, t_cub3d *cub)
{
	(void)key;
	(void)cub;
	exit(1);
	return (0);
}
