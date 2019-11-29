/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 10:04:43 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:25:36 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

void			img_init(t_win *win, t_img *img)
{
	img->img_ptr = mlx_new_image(win->mlx, win->l, win->h);
	img->img_addr = mlx_get_data_addr(img->img_ptr, &img->byte_px,
		&img->size_line, &img->endian);
}

void			destroy_img(t_win *win, t_img *img_sprite)
{
	mlx_destroy_image(win->mlx, img_sprite->img_ptr);
	img_sprite->img_addr = 0;
	img_sprite->img_ptr = 0;
}

t_cara			*setup_char(t_cub3d *cub, t_game *game)
{
	cub->cara->posx = (double)(game->y);
	cub->cara->posy = (double)(game->x);
	cub->cara->dirx = 0;
	cub->cara->diry = 0;
	cub->cara->planx = 0;
	cub->cara->plany = 0;
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
	cub->cara->ms = 0.1;
	cub->cara->rs = 0.1;
	return (cub->cara);
}

static t_cub3d	*setup(t_game *game)
{
	t_cub3d	*cub;

	if ((cub = malloc(sizeof(t_cub3d))) == NULL)
		return (NULL);
	if ((cub->img = malloc(sizeof(t_img))) == NULL)
		return (NULL);
	if ((cub->img_sprite = malloc(sizeof(t_img))) == NULL)
		return (NULL);
	if ((cub->win = malloc(sizeof(t_win))) == NULL)
		return (NULL);
	if ((cub->line = malloc(sizeof(t_line))) == NULL)
		return (NULL);
	if ((cub->cara = malloc(sizeof(t_cara))) == NULL)
		return (NULL);
	cub->map = game->map;
	if ((cub->win->mlx = mlx_init()) == NULL)
		return (NULL);
	cub->win->l = game->win.height;
	cub->win->h = game->win.width;
	cub->win->bmp = game->win.bmp;
	cub->cara = setup_char(cub, game);
	if ((cub->win->win = mlx_new_window(cub->win->mlx,
	game->win.height, game->win.width, NAME_WIN)) == NULL)
		return (NULL);
	return (cub);
}

int				ray(t_game *game)
{
	t_cub3d	*cub;

	if ((cub = setup(game)) == NULL)
		return (EXIT_FAILURE);
	hook_init(cub);
	img_init(cub->win, cub->img);
	cub->entry = get_tex(game->texture, cub->win);
	mlx_loop_hook(cub->win->mlx, loop_hook, cub);
	mlx_loop(cub->win->mlx);
	return (EXIT_FAILURE);
}
