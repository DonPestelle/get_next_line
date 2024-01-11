/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestelle <pestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:58:16 by pestelle          #+#    #+#             */
/*   Updated: 2024/01/10 18:46:06 by pestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_free(char **buffer)
{
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

char	*ft_next(char *buffer)
{
	int		i;
	char	*updated;
	int		j;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return (ft_free(&buffer));
	i++;
	updated = malloc(sizeof(char) * (ft_strlen(buffer) - i) + 1);
	if (!updated)
		return (ft_free(&buffer));
	j = 0;
	while (buffer[i])
		updated[j++] = buffer[i++];
	updated[j] = '\0';
	free(buffer);
	return (updated);
}

char	*ft_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(&res));
	buffer[0] = '\0';
	byte_read = 1;
	while (byte_read > 0 && !ft_strchr(buffer, '\n'))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			return (ft_free(&res));
		}
		if (byte_read > 0)
		{
			buffer[byte_read] = '\0';
			res = ft_strjoin(res, buffer);
		}
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*buffer = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(&buffer));
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	if (!line)
		return (ft_free(&buffer));
	buffer = ft_next(buffer);
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*putito;

	fd = open("file.txt", O_RDONLY);
	putito = get_next_line(fd);
	while (putito != NULL)
	{
		if (putito)
		{
			printf("result  ========= %s %p\n", putito, putito);
			free(putito);
		}
		putito = get_next_line(fd);
	}
	close(fd);
	return (0);
}*/
