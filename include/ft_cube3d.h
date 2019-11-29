/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube3d.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 00:02:07 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:24:27 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUBE3D_H
# define FT_CUBE3D_H

# include <libft.h>
# include <get_next_line.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <libc.h>
# define N_TEX 7
# define NAME_WIN "Cube3d"
# define PLAN_Y	0.66
# define POS_X	10;
# define POS_Y	12;

typedef struct	s_win
{
	void		*win;
	void		*mlx;
	int			height;
	int			width;
	int			l;
	int			h;
	int			w;
	int			a;
	int			s;
	int			d;
	int			lar;
	int			rar;
	int			bmp;
}				t_win;

typedef struct	s_player
{
	int			x;
	int			y;
	char		face;
}				t_player;

typedef struct	s_color
{
	int			red;
	int			blue;
	int			green;
}				t_color;

typedef	struct	s_texture
{
	char		*north_text;
	char		*south_text;
	char		*east_text;
	char		*west_text;
	char		*wall_text;
	t_color		roof;
	t_color		floor;
}				t_texture;

typedef	struct	s_map
{
	int			height;
	int			width;
	int			**map;
}				t_map;

typedef struct	s_game
{
	t_win		win;
	t_player	player;
	t_texture	texture;
	t_map		map;
	int			x;
	int			y;
	char		face;
}				t_game;

typedef struct	s_line
{
	double		camx;
	double		ray_dirx;
	double		ray_diry;
	double		side_distx;
	double		side_disty;
	double		delta_distx;
	double		delta_disty;
	double		wall_size;
	long double	wall_hit;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			side;
	int			lineh;
	int			start;
	int			end;
}				t_line;

typedef struct	s_img
{
	void		*img_ptr;
	char		*img_addr;
	int			byte_px;
	int			size_line;
	int			endian;
	int			height;
	int			width;
}				t_img;

typedef struct	s_cara
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		ms;
	double		rs;
	double		planx;
	double		plany;
}				t_cara;

typedef struct	s_entry
{
	t_img		*no_tex;
	t_img		*so_tex;
	t_img		*we_tex;
	t_img		*ea_tex;
	t_img		*sprite1;
	int			f_r;
	int			f_g;
	int			f_b;
	int			c_r;
	int			c_g;
	int			c_b;
}				t_entry;

typedef struct	s_cub3d
{
	t_win		*win;
	t_img		*img;
	t_img		*img_sprite;
	t_cara		*cara;
	t_line		*line;
	t_entry		*entry;
	t_map		map;
}				t_cub3d;

int				ft_printf(const char *format, ...);
void			ft_free_tab(void **tab);
int				len_digit(char *str);
int				str_strlen(char **tab);
int				check_map(t_game *game);
int				get_next_line(int fd, char **line, char *wich);
int				get_next_line_map(int fd, char **line);
int				parse_file(t_game *game, char *path);
int				parse_map(t_game *game, char *path);
int				parse_wall(t_game *game, char *path);
int				parse_color(t_game *game, char *path);
int				free_parse(char *line, void **res);
int				check_first_char(char *line, char *wich);
int				get_first_line(int fd, char **line);
int				ray(t_game *game);
void			move_front(t_cara *cara, t_map map);
void			move_back(t_cara *cara, t_map map);
void			move_left(t_cara *cara, t_map map);
void			move_right(t_cara *cara, t_map map);
void			hook_init(t_cub3d *cub);
int				exit_prog(int key, t_cub3d *cub);
void			destroy_win(t_win *win);
void			destroy_img(t_win *win, t_img *img_sprite);
int				loop_hook(t_cub3d *cub);
void			line_sprite(t_cub3d *cub);
void			line_wall(t_cub3d *cub);
void			rotate_right(t_cara *cara);
void			rotate_left(t_cara *cara);
int				dda_algo(t_line *line, t_map map);
int				dda_algo_sprite(t_line *line, t_map map);
void			draw_tex(t_cub3d *cub, t_img *tex, int i);
void			draw_font(t_img *img, t_win *win, t_entry *entry);
void			draw_map(t_img *img, t_win *win, t_cub3d *cub);
void			draw_sprite(t_cub3d *cub, int i);
void			draw_wall(t_cub3d *cub, int i);
void			line_init(t_line *line, t_cara *cara, t_win *win, int i);
t_entry			*get_tex(t_texture texture, t_win *win);

#endif
