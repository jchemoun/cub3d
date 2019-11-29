/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 00:04:20 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/27 14:14:15 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line_map.h>

static char	*ft_substrfr(char *s, unsigned int start, size_t len)
{
	char	*temp;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((temp = (char*)malloc((len + 1) * sizeof(char))) == NULL)
		return (NULL);
	temp[len] = '\0';
	while (len--)
	{
		temp[i] = s[start];
		i++;
		start++;
	}
	free(s);
	return (temp);
}

static int	check_line(char **str, char **line)
{
	int i;

	i = -1;
	while ((*str)[++i] && i < (int)ft_strlen(*str))
	{
		if ((*str)[i] == '\n')
		{
			if (i == 0)
			{
				if (((*line) = ft_strdup("")) == NULL)
					return (-1);
				*str = ft_substrfr(*str, i + 1, ft_strlen(*str));
			}
			else
			{
				if (((*line) = ft_substr(*str, 0, i)) == NULL)
					return (-1);
				*str = ft_substrfr(*str, i + 1, ft_strlen(*str));
			}
			return (1);
		}
	}
	return (0);
}

static int	free_all(char **str, char *buff, int crit)
{
	if (*str && (crit == -1 || crit == 0))
	{
		free(*str);
		*str = NULL;
	}
	if (buff != NULL)
		free(buff);
	if (crit == -1)
		return (-1);
	else if (crit)
		return (1);
	return (0);
}

static int	setup(char **buff, char **str, char **line, int fd)
{
	int ret;

	if (!(*buff = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (!*str)
	{
		if (!(*str = (char*)ft_calloc((BUFFER_SIZE + 1), sizeof(char))))
			return (-1);
		(*str)[BUFFER_SIZE] = '\0';
	}
	if (*str)
	{
		ret = check_line(str, line);
		if (ret == -1)
			return (-1);
		else if (ret)
			return (1);
	}
	return (0);
}

int			get_next_line_map(int fd, char **line)
{
	char		*buff;
	int			ret;
	static char	*str;

	if ((ret = setup(&buff, &str, line, fd)) == -1)
		return (free_all(&str, buff, -1));
	if (ret)
		return (free_all(&str, buff, 1));
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		str = ft_strjoinfr(str, buff);
		free(buff);
		buff = NULL;
		if ((ret = check_line(&str, line)) == -1)
			return (free_all(&str, buff, -1));
		if (ret)
			return (free_all(&str, buff, 1));
		if (!(buff = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (free_all(&str, buff, -1));
	}
	if (ret == -1 || ((*line) = ft_substr(str, 0, ft_strlen(str))) == NULL)
		return (free_all(&str, buff, -1));
	return (free_all(&str, buff, 0));
}
