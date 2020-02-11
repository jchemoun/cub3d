/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 09:43:47 by jchemoun          #+#    #+#             */
/*   Updated: 2020/02/04 09:49:28 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

void	setup_char2(t_cub3d *cub, t_game *game)
{
	if ((int)game->face == 'N')
	{
		cub->cara->dirx = -1;
		cub->cara->plany = 0.66;
	}
	else if ((int)game->face == 'S')
	{
		cub->cara->dirx = 1;
		cub->cara->plany = -0.66;
	}
	else if ((int)game->face == 'E')
	{
		cub->cara->diry = 1;
		cub->cara->planx = 0.66;
	}
	else if ((int)game->face == 'W')
	{
		cub->cara->diry = -1;
		cub->cara->planx = -0.66;
	}
}
