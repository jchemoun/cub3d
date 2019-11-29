/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_map.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 00:03:11 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:14:14 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line_map.h>

char			*ft_strcpyo(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (src == NULL && dest == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char			*ft_strjoinfr(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	int		len;
	char	*str;

	i = -1;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len1 = (int)ft_strlen(s1);
	len2 = (int)ft_strlen(s2);
	if ((str = (char*)malloc(len1 + len2 + 1)) == NULL)
		return (NULL);
	str = ft_strcpyo(str, s1, len1);
	str[len1 + len2] = '\0';
	len = len1;
	while (++i < (int)len2)
		str[len + i] = s2[i];
	free((char*)s1);
	return (str);
}
