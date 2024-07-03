/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:37:08 by adrgutie          #+#    #+#             */
/*   Updated: 2024/06/26 20:55:15 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	freeptr(char **p1, char **p2, char **p3)
{
	if (p1)
	{
		if (*p1)
			free(*p1);
		*p1 = NULL;
	}
	if (p2)
	{
		if (*p2)
			free(*p2);
		*p2 = NULL;
	}
	if (p3)
	{
		if (*p3)
			free(*p3);
		*p3 = NULL;
	}
}

static char	*leftovercheck(char **leftover,char **line)
{
	char	*temp;
	char	*end;
	size_t	i;

	i = 0;
	while ((*leftover)[i] != '\n' && (*leftover)[i] != 0)
		i++;
	if ((*leftover)[i] == '\n')
	{
		end = free_ft_substr(leftover, 0, i + 1);
		*line = free_ft_strjoin(line, &end);
		temp = *leftover;
		*leftover = free_ft_substr(leftover, i + 1, ft_strlen(*leftover));
		if (*leftover == NULL || *line == NULL)
			return (freeptr(&temp, line, NULL), NULL);
		free(temp);
	}
	else
	{
		end = free_ft_substr(leftover, 0, ft_strlen(*leftover));
		*line = free_ft_strjoin(line, &end);
		freeptr(leftover, NULL, NULL);
	}
	return (*line);
}
char	*rescheck(char **line, char **leftover)
{
		if (!(*line))
			return (freeptr(line, leftover, NULL), NULL);
		if (*leftover)
			return (*line);
}
static char	*getline(int fd, char **leftover)
{
	ssize_t	bytesread;
	char	*line;

	line = (char *)malloc(1);
	if (!line)
		return (freeptr(&line, leftover, NULL), NULL);
	line[0] = 0;
	bytesread = 1;
	while (bytesread > 0)
	{
		line = leftovercheck(leftover, &line);
		if (!line || (*leftover))
			return (rescheck(&line, leftover));
		*leftover = (char *)malloc(BUFFER_SIZE + 1);
		if (!(*leftover))
			return (freeptr(&line, leftover, NULL), NULL);
		bytesread = read(fd, *leftover, BUFFER_SIZE);
		if (bytesread < 0)
			return (freeptr(&line, leftover, NULL), NULL);
		(*leftover)[bytesread] = 0;
	}
	if (line) 
		return (line);
	return (freeptr(&line, leftover, NULL), NULL);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char 		*line;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	if (!leftover)
	{
		leftover = (char *)malloc(BUFFER_SIZE + 1);
		if (!leftover)
			return (NULL);
		leftover[0] = 0;
	}
	line = getline(fd, &leftover);
	if (line)
	{
		if (line[0] == 0)
			return (freeptr(&line, &leftover, NULL), NULL);
		return (line);
	}
	return (freeptr(&line, &leftover, NULL), NULL);
}
