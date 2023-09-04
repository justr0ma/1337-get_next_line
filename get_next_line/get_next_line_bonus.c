/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halaqoh <halaqoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:00:32 by halaqoh           #+#    #+#             */
/*   Updated: 2021/12/03 17:32:46 by halaqoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
//#define BUFFER_SIZE 4

char	*get_line_bonus(char *str)
{
	char	*line;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		line = malloc((sizeof(char) * i) + 2);
	else
		line = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	if (str[i] == '\n')
	{
		line[j] = '\n';
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*get_next_bonus(char *str)
{
	int		i;
	char	*new_line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
	{
		new_line = ft_strdup(str + i + 1);
		free(str);
		return (new_line);
	}
	free(str);
	return (NULL);
}

char	*ft_read(char *str, int fd)
{
	int		retread;
	char	*buf;

	retread = 1;
	buf = malloc(BUFFER_SIZE + 1);
	while (retread != 0 && !ft_strchr(str))
	{
		retread = read(fd, buf, BUFFER_SIZE);
		if (retread < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[retread] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	char			*line;
	int				retread;
	static char		*str[1024];

	retread = 1;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	str[fd] = ft_read(str[fd], fd);
	if (!str[fd])
		return (NULL);
	if (str[fd][0] == '\0')
	{
		free(str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	line = get_line_bonus(str[fd]);
	str[fd] = get_next_bonus(str[fd]);
	return (line);
}
