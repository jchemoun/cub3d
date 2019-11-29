/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 02:56:44 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:07:13 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

t_img	*get_img_from_file(t_win *win, char *filename)
{
	t_img	*tex;

	if (!(tex = malloc(sizeof(t_img))))
		return (0);
	tex->img_ptr = mlx_xpm_file_to_image(win->mlx, filename,
	&tex->width, &tex->height);
	if (tex->img_ptr == 0)
	{
		free(tex);
		return (0);
	}
	tex->img_addr = mlx_get_data_addr(tex->img_ptr, &tex->byte_px,
		&tex->size_line, &tex->endian);
	return (tex);
}

t_entry	*get_tex(t_texture texture, t_win *win)
{
	int		i;
	t_entry	*entry;

	i = 1;
	if (!(entry = malloc(sizeof(t_entry))))
		return (0);
	entry->no_tex = get_img_from_file(win, texture.north_text);
	entry->so_tex = get_img_from_file(win, texture.south_text);
	entry->we_tex = get_img_from_file(win, texture.west_text);
	entry->ea_tex = get_img_from_file(win, texture.east_text);
	entry->sprite1 = get_img_from_file(win, texture.wall_text);
	entry->f_r = texture.floor.red;
	entry->f_g = texture.floor.green;
	entry->f_b = texture.floor.blue;
	entry->c_r = texture.roof.red;
	entry->c_g = texture.roof.green;
	entry->c_b = texture.roof.blue;
	return (entry);
}