/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 07:50:43 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:10:37 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_cube3d.h>

int	len_digit(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	return (1);
}

int	free_parse(char *line, void **res)
{
	if (line)
		free(line);
	if (res)
		ft_free_tab(res);
	return (EXIT_FAILURE);
}

int	str_strlen(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}
