/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 01:46:23 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:21:55 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

void	move_front(t_cara *cara, t_map map)
{
	if (map.map[(int)(cara->posx + (cara->dirx * (cara->ms *
		2.0)))][(int)(cara->posy)] == 0)
		cara->posx += (cara->dirx * cara->ms);
	if (map.map[(int)(cara->posx)][(int)(cara->posy + cara->diry *
		(cara->ms * 2.0))]
		== 0)
		cara->posy += cara->diry * cara->ms;
}

void	move_back(t_cara *cara, t_map map)
{
	if (map.map[(int)(cara->posx - (cara->dirx * (cara->ms *
		2.0)))][(int)(cara->posy)] == 0)
		cara->posx -= (cara->dirx * cara->ms);
	if (map.map[(int)(cara->posx)][(int)(cara->posy - cara->diry *
		(cara->ms * 2.0))] == 0)
		cara->posy -= (cara->diry * cara->ms);
}

void	move_left(t_cara *cara, t_map map)
{
	if (map.map[(int)(cara->posx)][(int)(cara->posy + ((cara->ms *
		2.0) * cara->dirx))] == 0)
		cara->posy += (cara->ms * cara->dirx);
	if (map.map[(int)(cara->posx + ((cara->ms * 2.0) *
		cara->diry))][(int)(cara->posy)] == 0)
		cara->posx += -(cara->ms * cara->diry);
}

void	move_right(t_cara *cara, t_map map)
{
	if (map.map[(int)(cara->posx)][(int)(cara->posy - ((cara->ms *
		2.0) * cara->dirx))] == 0)
		cara->posy -= (cara->ms * cara->dirx);
	if (map.map[(int)(cara->posx + ((cara->ms * 2.0) *
		cara->diry))][(int)(cara->posy)] == 0)
		cara->posx -= -(cara->ms * cara->diry);
}
