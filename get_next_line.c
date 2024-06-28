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

char	*freeptr(char **line, char	**leftover)
{
	if (*line)
		free(*line);
	*line = NULL;
	if (*leftover)
		free(*leftover);
	*leftover = NULL;
	return (NULL);
}

char	*leftovercheck(char **leftover,char **line)
{
	char	*temp;
	char	*end;

	temp = *leftover;
	while (*temp != '\n' && *temp != 0)
		temp++;
	if (*temp == '\n')
	{
		end = ft_substr(*leftover, 0, (temp + 1) - *leftover);
		*line = fl_ft_strjoin(line, end);
		temp = *leftover;
		*leftover = ft_substr(*leftover, ft_strlen(end), ft_strlen(*leftover));
		free(temp);
	}
	else
	{
		end = ft_substr(*leftover, 0, ft_strlen(*leftover));
		*line = fl_ft_strjoin(line, end);
		free(*leftover);
		*leftover = NULL;
	}
	free(end);
	return (*line);
}

char	*getline(int fd, char **leftover)
{
	ssize_t	bytesread;
	char	*line;

	line = (char *)malloc(1);
	if (!line)
		return (freeptr(&line, leftover));
	line[0] = 0;
	bytesread = 1;
	while (bytesread > 0)
	{
		line = leftovercheck(leftover, &line);		
		if (*leftover)
			return (line);
		*leftover = (char *)malloc(BUFFER_SIZE + 1);
		if (!(*leftover))
			return (freeptr(&line, leftover));
		bytesread = read(fd, *leftover, BUFFER_SIZE);
		(*leftover)[bytesread] = 0;
	}
	if (ft_strlen(line))  // If there's any data left in line after the end of the file is reached
		return (line);
	else
		return (freeptr(&line, leftover));
}

char	*get_next_line(int fd)
{
	static char	*leftover;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	if (!leftover)
	{
		leftover = (char *)malloc(BUFFER_SIZE + 1);
		if (!leftover)
			return (NULL);
		leftover[0] = 0;
	}
	return (getline(fd, &leftover));
}
