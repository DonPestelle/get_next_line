/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestelle <pestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:58:42 by pestelle          #+#    #+#             */
/*   Updated: 2025/03/17 15:42:12 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && (char)c != *s)
		s++;
	if ((char)c == *s)
		return ((char *)s);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (ft_free(&s1));
	i = -1;
	while (s1[++i] != '\0')
		s3[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		s3[i++] = s2[j++];
	s3[i] = '\0';
	ft_free(&s1);
	return (s3);
}

size_t	ft_strlen(const char *s)
{
	size_t	l;

	if (!s)
		return (0);
	l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}
