/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:53:01 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/14 10:44:18 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
//#include <mlx_opengl.h>
#include <mlx.h>
#include <math.h>

#define N_TEX 7

int map[5][6]=
{
	{1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 1},
	{1, 0, 2, 0, 0, 1},
	{1, 1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1}
};

typedef struct	s_line
{
	double	camx;
	double	ray_dirx;
	double	ray_diry;
	double	side_distx;
	double	side_disty;
	double	delta_distx;
	double	delta_disty;
	double	wall_size;
	long double	wall_hit;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		side;
	int		lineh;
	int		start;
	int		end;
}				t_line;

typedef struct	s_win
{
	void	*win;
	void	*mlx;
	int		l;
	int		h;
	int		w;
	int		a;
	int		s;
	int		d;
	int		lar;
	int		rar;
}				t_win;

typedef struct	s_img
{
	void	*img_ptr;
	char	*img_addr;
	int		byte_px;
	int		size_line;
	int		endian;
	int		height;
	int		width;
}				t_img;

typedef struct	s_cara
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	ms;
	double	rs;
	double	planx;
	double	plany;
	//int	map[24][24];
}				t_cara;

typedef struct	s_entry
{
	t_img	*no_tex;
	t_img	*so_tex;
	t_img	*we_tex;
	t_img	*ea_tex;
	t_img	*sprite1;
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
	//int		f_color[3];
	//int		c_color[3];
}				t_entry;

typedef struct	s_cub3d
{
	t_win		*win;
	t_img		*img;
	t_cara		*cara;
	t_line		*line;
	t_entry		*entry;
}				t_cub3d;

void	draw_font(t_img *img, t_win *win, t_entry *entry)
{
	int i;
	int j;

	i = 0;
	j = 0;
	//printf("%i	%i	%i\n", entry->c_r, entry->c_g, entry->c_b);
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

void	draw_img(t_win *win, t_line *line, t_cara *cara, t_img *img)
{
	int i;
	int j;
	int hit;
	int side;

	i = 0;
	while (i < win->h)
	{
		j = 0;
		while (j < win->l)
		{
			*(img->img_addr + (j * 4 + 0) + (img->size_line * i)) = (i < win->h / 2) ? 0 : (unsigned char)255;
			*(img->img_addr + (j * 4 + 1) + (img->size_line * i)) = (i < win->h / 2) ? 0 : (unsigned char)255;
			*(img->img_addr + (j * 4 + 2) + (img->size_line * i)) = (i < win->h / 2) ? 0 : (unsigned char)255;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < win->l)
	{
		hit = 0;
		line->mapx = (int)cara->posx;
		line->mapy = (int)cara->posy;
		line->camx = (2 * i / (double)win->l) - 1;
		line->ray_dirx = cara->dirx + cara->planx * line->camx;
		line->ray_diry = cara->diry + cara->plany * line->camx;
		line->delta_distx = fabs(1 / line->ray_dirx);
		line->delta_disty = fabs(1 / line->ray_diry);
		if (line->ray_dirx < 0)
		{
			line->stepx = -1;
			line->side_distx = (cara->posx - line->mapx) * line->delta_distx;
		}
		else
		{
			line->stepx = 1;
			line->side_distx = (line->mapx + 1.0 - cara->posx) * line->delta_distx;
		}
		if (line->ray_diry < 0)
		{
			line->stepy = -1;
			line->side_disty = (cara->posy - line->mapy) * line->delta_disty;
		}
		else
		{
			line->stepy = 1;
			line->side_disty = (line->mapy + 1.0 - cara->posy) * line->delta_disty;
		}
		//printf("%i	%i\n", line->stepy, line->stepx);
		while (!hit)
		{
			if (line->side_distx < line->side_disty)
			{
				line->side_distx += line->delta_distx;
				line->mapx += line->stepx;
				side = 0;
			}
			else
			{
				line->side_disty += line->delta_disty;
				line->mapy += line->stepy;
				side = 1;
			}
			hit = map[line->mapx][line->mapy] == 1 ? 1 : 0;
		}
		//printf("%i	%i	%i	%i	%i	%f\n", i, side, line->mapx, cara->posx, line->stepx, line->ray_dirx);
		line->wall_size = side == 0 ?
			(line->mapx - cara->posx + (1 - line->stepx) / 2) / line->ray_dirx :
			(line->mapy - cara->posy + (1 - line->stepy) / 2) / line->ray_diry;
		line->lineh = (int)(win->h / line->wall_size);
		line->start = -line->lineh / 2 + win->h / 2;
		line->start = line->start < 0 ? 0 : line->start;
		line->end = (line->lineh / 2) + (win->h / 2);
		line->end = line->end >= win->h ? win->h : line->end;
		j = line->start;
		//printf("%i	%i	%i\n", i, j, line->end);
		//printf("lineh%i		WALL%Lf\n", line->lineh, line->wall_size);
		while (j < line->end)
		{
			//printf("%i	%i\n", i, j);
			*(img->img_addr + (i * 4 + 0) + (img->size_line * j)) = (unsigned char)0;
			*(img->img_addr + (i * 4 + 1) + (img->size_line * j)) = (unsigned char)0;
			*(img->img_addr + (i * 4 + 2) + (img->size_line * j)) = (unsigned char)255 / (side + 1);
			j++;
		}
		i++;
	}
}

int		dda_algo(t_line *line)
{
	int hit;
	int side;

	hit = 0;
	while (!hit)
	{
		if (line->side_distx < line->side_disty)
		{
			line->side_distx += line->delta_distx;
			line->mapx += line->stepx;
			side = 0;
		}
		else
		{
			line->side_disty += line->delta_disty;
			line->mapy += line->stepy;
			side = 1;
		}
		hit = map[line->mapx][line->mapy] == 1 ? 1 : 0;
	}
	return (side);
}

void	line_init(t_line *line, t_cara *cara, t_win *win, int i)
{
	line->camx = (2 * i / (double)win->l) - 1;
	line->ray_dirx = cara->dirx + cara->planx * line->camx;
	line->ray_diry = cara->diry + cara->plany * line->camx;
	line->delta_distx = fabs(1 / line->ray_dirx);
	line->delta_disty = fabs(1 / line->ray_diry);
	if (line->ray_dirx < 0)
	{
		line->stepx = -1;
		line->side_distx = (cara->posx - line->mapx) * line->delta_distx;
	}
	else
	{
		line->stepx = 1;
		line->side_distx = (line->mapx + 1.0 - cara->posx) * line->delta_distx;
	}
	if (line->ray_diry < 0)
	{
		line->stepy = -1;
		line->side_disty = (cara->posy - line->mapy) * line->delta_disty;
	}
	else
	{
		line->stepy = 1;
		line->side_disty = (line->mapy + 1.0 - cara->posy) * line->delta_disty;
	}
}

void	draw_wall(t_cub3d *cub, int i)
{
	int texx;
	int texy;
	t_img *tex = cub->entry->no_tex;

	//printf("%i	%i\n", tex->height, tex->width);
	texx = ((int)(cub->line->wall_hit * (double)tex->width));
	if (cub->line->side == 1 && cub->line->ray_dirx > 0)
		texx = tex->width - texx - 1;
	if (cub->line->side == 0 && cub->line->ray_diry < 0)
		texx = tex->width - texx - 1;
	//printf("%i	%i\n", cub->img->byte_px, tex->size_line);
	while (cub->line->start < cub->line->end)
	{
		texy = ((((cub->line->start * 256) - (cub->win->h * 128) + (cub->line->lineh * 128)) * tex->height) / cub->line->lineh) / 256;
		//printf("%i	%i\n", texx, texy);
		*(cub->img->img_addr + (i * 4 + 0) + (cub->img->size_line * cub->line->start)) = *(tex->img_addr + (texy * 4 + 0) + (tex->size_line * texx));
		*(cub->img->img_addr + (i * 4 + 1) + (cub->img->size_line * cub->line->start)) = *(tex->img_addr + (texy * 4 + 1) + (tex->size_line * texx));
		*(cub->img->img_addr + (i * 4 + 2) + (cub->img->size_line * cub->line->start)) = *(tex->img_addr + (texy * 4 + 2) + (tex->size_line * texx));
		*(cub->img->img_addr + (i * 4 + 3) + (cub->img->size_line * cub->line->start)) = *(tex->img_addr + (texy * 4 + 3) + (tex->size_line * texx));
		cub->line->start++;
	}
	/*
	(void)entry;
	while (line->start < line->end)
	{
		//printf("%i	%i\n", i, line->start);
		*(img->img_addr + (i * 4 + 0) + (img->size_line * line->start)) = (unsigned char)0;
		*(img->img_addr + (i * 4 + 1) + (img->size_line * line->start)) = (unsigned char)0;
		*(img->img_addr + (i * 4 + 2) + (img->size_line * line->start)) = (unsigned char)255;
		line->start++;
	}
	*/
}

void	line_wall(t_cub3d *cub)
{
	int hit;
	int i;

	i = 0;
	while (i < cub->win->l)
	{
		hit = 0;
		cub->line->mapx = (int)cub->cara->posx;
		cub->line->mapy = (int)cub->cara->posy;
		line_init(cub->line, cub->cara, cub->win, i);
		if ((cub->line->side = dda_algo(cub->line) == 0))
			cub->line->wall_size = (cub->line->mapx - cub->cara->posx +
				(1 - cub->line->stepx) / 2) / cub->line->ray_dirx;
		else
			cub->line->wall_size = (cub->line->mapy - cub->cara->posy +
				(1 - cub->line->stepy) / 2) / cub->line->ray_diry;
		cub->line->lineh = (int)(cub->win->h / cub->line->wall_size);
		if ((cub->line->start = -cub->line->lineh / 2 + cub->win->h / 2) < 0)
			cub->line->start = 0;
		if ((cub->line->end = (cub->line->lineh / 2) + (cub->win->h / 2))
			>= cub->win->h)
			cub->line->end = cub->win->h;
		//for tex
		//printf("%f	%f	%f\n", cub->cara->posx, cub->line->wall_size, cub->line->ray_dirx);
		//printf("%f %f\n", (double)(cub->line->wall_size * cub->line->ray_dirx), cub->cara->posx);
		//printf("printadd%f\n", (double)(cub->line->wall_size * cub->line->ray_dirx) + cub->cara->posx);
		if (cub->line->side == 1)
			cub->line->wall_hit = cub->cara->posy + (double)(cub->line->wall_size * cub->line->ray_diry);
		else
			cub->line->wall_hit = (cub->line->wall_size * cub->line->ray_dirx) + cub->cara->posx;
		//printf("WAllhit%Lf	%f\n", cub->line->wall_hit, (double)floor(cub->line->wall_hit));
		cub->line->wall_hit -= floor(cub->line->wall_hit);
		//printf("postfloor%f\n", cub->line->wall_hit);
		//end for
		draw_wall(cub, i);
		i++;
	}
}

void	get_color_c(char *color, t_entry *entry)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (color[i] > 47 && color[i] < 58)
	{
		r = r * 10 + color[i] - 48;
		i++;
	}
	//printf("%i\n", r);
	entry->c_r = r;
	r = 1 - !!(++i);
	while (color[i] > 47 && color[i] < 58)
	{
		r = r * 10 + color[i] - 48;
		i++;
	}
	entry->c_b = r;
	r = 1 - !!(++i);
	while (color[i] > 47 && color[i] < 58)
	{
		r = r * 10 + color[i] - 48;
		i++;
	}
	entry->c_g = r;
}

void	get_color_f(char *color, t_entry *entry)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (color[i] > 47 && color[i] < 58)
	{
		r = r * 10 + color[i] - 48;
		i++;
	}
	//printf("%i\n", r);
	entry->f_r = r;
	r = 1 - !!(++i);
	while (color[i] > 47 && color[i] < 58)
	{
		r = r * 10 + color[i] - 48;
		i++;
	}
	entry->f_g = r;
	r = 1 - !!(++i);
	while (color[i] > 47 && color[i] < 58)
	{
		r = r * 10 + color[i] - 48;
		i++;
	}
	entry->f_b = r;
}

t_img	*get_img_from_file(t_win *win, char *filename)
{
	t_img	*tex;

	if (!(tex = malloc(sizeof(t_img))))
		return (0);
	tex->img_ptr = mlx_xpm_file_to_image(win->mlx, filename, &tex->width, &tex->height);
	if (tex->img_ptr == 0)
	{
		free(tex);
		return (0);
	}
	tex->img_addr = mlx_get_data_addr(tex->img_ptr, &tex->byte_px,
		&tex->size_line, &tex->endian);
	return (tex);
}

t_entry	*get_tex(char *path_tab[N_TEX], t_win *win)
{
	int		i;
	t_entry	*entry;

	i = 0;
	if (!(entry = malloc(sizeof(t_entry))))
		return (0);
	entry->no_tex = get_img_from_file(win, path_tab[i++]);
	entry->so_tex = get_img_from_file(win, path_tab[i++]);
	entry->we_tex = get_img_from_file(win, path_tab[i++]);
	entry->ea_tex = get_img_from_file(win, path_tab[i++]);
	entry->sprite1 = get_img_from_file(win, path_tab[i++]);
	get_color_f(path_tab[i++], entry);
	get_color_c(path_tab[i], entry);
	//printf("fgh%i\n", entry->f_r);
	return (entry);
}

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
	if (key == 0)
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

void	hook_init(t_win *win)
{
	mlx_do_key_autorepeatoff(win->mlx);
	mlx_hook(win->win, 2, 0, key_press_hook, win);
	mlx_hook(win->win, 3, 0, key_release_hook, win);
}

void	img_init(t_win *win, t_img *img)
{
	img->img_ptr = mlx_new_image(win->mlx, win->l, win->h);
	img->img_addr = mlx_get_data_addr(img->img_ptr, &img->byte_px,
		&img->size_line, &img->endian);
}

void	move_front(t_cara *cara)
{
	//printf("%f	%f\n", cara->posx, cara->posy);
	if (map[(int)(cara->posx + (cara->dirx * cara->ms))][(int)(cara->posy)]
		!= 1)
		cara->posx += (cara->dirx * cara->ms);
	//printf("%f	%f\n", cara->posx, cara->posy);
	if (map[(int)(cara->posx)][(int)(cara->posy+ cara->diry * cara->ms)]
		!= 1)
		cara->posy += cara->diry * cara->ms;
}

void	move_back(t_cara *cara)
{
	//printf("%f	%f\n", cara->posx, cara->posy);
	if (map[(int)(cara->posx - (cara->dirx * cara->ms))][(int)(cara->posy)]
		!= 1)
		cara->posx -= (cara->dirx * cara->ms);
	//printf("%f	%f\n", cara->posx, cara->posy);
	if (map[(int)(cara->posx)][(int)(cara->posy - cara->diry * cara->ms)]
		!= 1)
		cara->posy -= (cara->diry * cara->ms);
}

void	move_left(t_cara *cara)
{
	if (map[(int)(cara->posx)][(int)(cara->posy + (cara->ms * cara->plany/*cara->dirx*/))]
		!= 1)
		cara->posy -= (cara->ms * cara->plany/*cara->dirx*/);
	if (map[(int)(cara->posx + (cara->ms * cara->diry))][(int)(cara->posy)]
		!= 1)
		cara->posx += -(cara->ms * cara->diry);
	//printf("%f	%f	%f	%f\n", cara->posy, cara->posx, cara->planx, cara->plany);
}

void	move_right(t_cara *cara)
{
	if (map[(int)(cara->posx)][(int)(cara->posy - (cara->ms * cara->dirx))]
		!= 1)
		cara->posy -= (cara->ms * cara->dirx);
	if (map[(int)(cara->posx + (cara->ms * cara->diry))][(int)(cara->posy)]
		!= 1)
		cara->posx -= -(cara->ms * cara->diry);
	//printf("%f	%f	%f	%f\n", cara->posy, cara->posx, cara->planx, cara->plany);
}

void	rotate_right(t_cara *cara)
{
	double	old_dir;
	double	old_planx;

	old_dir = cara->dirx;
	old_planx = cara->planx;
	cara->dirx = cara->dirx * cos(-cara->rs) - cara->diry * sin(-cara->rs);
	cara->diry = old_dir * sin(-cara->rs) + cara->diry * cos(-cara->rs);
	cara->planx = cara->planx * cos(-cara->rs) - cara->plany * sin(-cara->rs);
	cara->plany = old_planx * sin(-cara->rs) + cara->plany * cos(-cara->rs);
}

void	rotate_left(t_cara *cara)
{
	double	old_dir;
	double	old_planx;

	old_dir = cara->dirx;
	old_planx = cara->planx;
	cara->dirx = cara->dirx * cos(cara->rs) - cara->diry * sin(cara->rs);
	cara->diry = old_dir * sin(cara->rs) + cara->diry * cos(cara->rs);
	cara->planx = cara->planx * cos(cara->rs) - cara->plany * sin(cara->rs);
	cara->plany = old_planx * sin(cara->rs) + cara->plany * cos(cara->rs);
}

int		loop_hook(t_cub3d *cub)
{
	if (cub->win->w == 1)
		move_front(cub->cara);
	if (cub->win->s == 1)
		move_back(cub->cara);
	if (cub->win->a == 1)
		move_left(cub->cara);
	if (cub->win->d == 1)
		move_right(cub->cara);
	if (cub->win->rar == 1)
		rotate_right(cub->cara);
	if (cub->win->lar == 1)
		rotate_left(cub->cara);
	//printf("%d\n", cub->entry->f_r);
	draw_font(cub->img, cub->win, cub->entry);
	line_wall(cub);
	//draw_img(cub->win, cub->line, cub->cara, cub->img);
	mlx_put_image_to_window(cub->win->mlx, cub->win->win, cub->img->img_ptr, 0, 0);
	return (1);
}

int main(int ac, char *av[])
{
	t_win *test;
	t_img *img;
	t_line *line;
	t_cara *cara;
	t_cub3d	*cub;

	(void)ac;
	img = malloc(sizeof(t_img));
	test = malloc(sizeof(t_win));
	line = malloc(sizeof(t_line));
	cara = malloc(sizeof(t_cara));
	cub = malloc(sizeof(t_cub3d));
	cub->cara = cara;
	cub->img = img;
	cub->win = test;
	cub->line = line;
	test->mlx = mlx_init();
	test->l = 1920;
	test->h = 1080;
	test->win = mlx_new_window(test->mlx, 1920, 1080, "Title");
	hook_init(test);
	img_init(test, img);
	//printf("%p	%p	%i	%i	%i\n", img->img_ptr, img->img_addr, img->byte_px, img->size_line, img->endian);
	cara->posx = 3;
	cara->posy = 4;
	cara->dirx = -1;
	cara->diry = 0;
	cara->ms = 0.1;
	cara->rs = 0.1;
	cara->planx = 0;
	cara->plany = 0.66;
	cub->entry = get_tex(av + 1, test);
	//printf("123%i\n", entry->c_r);
	//draw_img(test, line, cara, img);
	//mlx_put_image_to_window(test->mlx, test->win, img->img_ptr, 0, 0);
	mlx_loop_hook(test->mlx, loop_hook, cub);
	//mlx_key_hook(cub->win->win, key_press_hook, cub->win);
	mlx_loop(test->mlx);
	return (0);
}
