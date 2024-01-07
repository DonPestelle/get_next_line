/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestelle <pestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:58:16 by pestelle          #+#    #+#             */
/*   Updated: 2024/01/07 17:07:58 by pestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *buffer)
{
	free(buffer);
	buffer = NULL;
	return (NULL);
}

char	*ft_next(char *buffer)
{
	int		i;
	char	*line;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		ft_free(buffer);
		return (NULL);
	}
	line = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	ft_free(buffer);
	return (line);
}

char	*ft_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;
	char	*temp;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = read(fd, buffer, BUFFER_SIZE);
	while (byte_read > 0)
	{
		if (byte_read == -1)
		{
			ft_free(buffer);
			return (ft_free(res));
		}
		buffer[byte_read] = '\0';
		temp = ft_strjoin(res, buffer);
		ft_free(res);
		res = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
		byte_read = read(fd, buffer, BUFFER_SIZE);
	}
	ft_free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (read(fd, 0, 0) < 0)
	{
		ft_free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(buffer[fd]);
	buffer[fd] = ft_next(buffer[fd]);
	if (line && line[0] == '\0')
	{
		ft_free(line);
		ft_free(buffer[fd]);
		return (NULL);
	}
	return (line);
}
