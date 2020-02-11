/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:35:04 by jchemoun          #+#    #+#             */
/*   Updated: 2020/01/23 15:05:35 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

static inline void	write_int(t_save *bmp, unsigned int a)
{
	bmp->buf[bmp->pos++] = a >> 0;
	bmp->buf[bmp->pos++] = a >> 8;
	bmp->buf[bmp->pos++] = a >> 16;
	bmp->buf[bmp->pos++] = a >> 24;
}

static inline void	write_header(t_save *bmp)
{
	bmp->buf[bmp->pos++] = 'B';
	bmp->buf[bmp->pos++] = 'M';
	write_int(bmp, bmp->size);
	write_int(bmp, 0);
	bmp->buf[bmp->pos++] = 54;
	bmp->buf[bmp->pos++] = 0;
	bmp->buf[bmp->pos++] = 0;
	bmp->buf[bmp->pos++] = 0;
}

static inline void	write_info(t_cub3d *cub, t_save *bmp)
{
	int i;

	i = 0;
	bmp->buf[bmp->pos++] = 40;
	bmp->buf[bmp->pos++] = 0;
	bmp->buf[bmp->pos++] = 0;
	bmp->buf[bmp->pos++] = 0;
	write_int(bmp, cub->win->l);
	write_int(bmp, cub->win->h);
	bmp->buf[bmp->pos++] = 1;
	bmp->buf[bmp->pos++] = 0;
	bmp->buf[bmp->pos++] = 24;
	bmp->buf[bmp->pos++] = 0;
	while (i < 24)
	{
		bmp->buf[bmp->pos++] = 0;
		i++;
	}
}

static inline void	write_img(t_cub3d *cub, t_save *bmp)
{
	int i;
	int j;

	i = cub->win->h - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < cub->win->l)
		{
			bmp->buf[bmp->pos++] = (*(cub->img->img_addr + i *
				cub->img->size_line + j * 4 + 0));
			bmp->buf[bmp->pos++] = (*(cub->img->img_addr + i *
				cub->img->size_line + j * 4 + 1));
			bmp->buf[bmp->pos++] = (*(cub->img->img_addr + i *
				cub->img->size_line + j * 4 + 2));
			j++;
		}
		j = 0;
		while (j < (4 - (cub->win->l * 3) % 4) % 4)
		{
			bmp->buf[bmp->pos++] = 0;
			j++;
		}
		i--;
	}
}

void				save_bmp(t_cub3d *cub)
{
	int		fd;
	t_save	bmp;

	bmp.size = 54 + 3 * cub->win->l * cub->win->h +
		((4 - (cub->win->l * 3) % 4) % 4) * cub->win->h;
	bmp.pos = 0;
	if (!(bmp.buf = malloc(bmp.size)))
	{
		ft_printf("Error save.\n");
		exit(0);
	}
	if ((fd = open("screenshot/save.bmp", O_WRONLY | O_CREAT)) < 0)
	{
		ft_printf("Error save fd.\n");
		exit(0);
	}
	write_header(&bmp);
	write_info(cub, &bmp);
	write_img(cub, &bmp);
	write(fd, bmp.buf, bmp.size);
	close(fd);
	exit(1);
}
