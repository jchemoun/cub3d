/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 02:25:38 by jchemoun          #+#    #+#             */
/*   Updated: 2020/02/06 14:38:39 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

void	rotate_right(t_cara *cara)
{
	float	old_dir;
	float	old_planx;

	old_dir = cara->dirx;
	old_planx = cara->planx;
	cara->dirx = cara->dirx * cos(-cara->rs) - cara->diry * sin(-cara->rs);
	cara->diry = old_dir * sin(-cara->rs) + cara->diry * cos(-cara->rs);
	cara->planx = cara->planx * cos(-cara->rs) - cara->plany * sin(-cara->rs);
	cara->plany = old_planx * sin(-cara->rs) + cara->plany * cos(-cara->rs);
}

void	rotate_left(t_cara *cara)
{
	float	old_dir;
	float	old_planx;

	old_dir = cara->dirx;
	old_planx = cara->planx;
	cara->dirx = cara->dirx * cos(cara->rs) - cara->diry * sin(cara->rs);
	cara->diry = old_dir * sin(cara->rs) + cara->diry * cos(cara->rs);
	cara->planx = cara->planx * cos(cara->rs) - cara->plany * sin(cara->rs);
	cara->plany = old_planx * sin(cara->rs) + cara->plany * cos(cara->rs);
}
