/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_macro.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:17:27 by jchemoun          #+#    #+#             */
/*   Updated: 2020/02/11 15:47:24 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

unsigned int	ft_abs(int x)
{
	return ((x < 0) ? -x : x);
}

int				ft_min(int a, int b)
{
	return ((((a) < (b)) ? (a) : (b)));
}

int				ft_max(int a, int b)
{
	return ((((a) > (b)) ? (a) : (b)));
}

void			ft_swap(int *a, int *b)
{
	int c;

	c = *a;
	*a = *b;
	*b = c;
}
