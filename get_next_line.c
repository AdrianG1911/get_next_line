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

char	*freeptr(char	**leftover)
{
	free(*leftover);
	*leftover = NULL;
	return (NULL);
}

char	*leftovercheck(char **leftover)
{
	char	*temp;
	char	*line;

	temp = *leftover;
	while (*temp != '\n' && *temp != 0)
		temp++;
	if (*temp == 0)
		temp = NULL;
	if (temp)
	{
		line = ft_substr(*leftover, 0, (temp + 1) - *leftover);
		temp = *leftover;
		*leftover = ft_substr(*leftover, ft_strlen(line), ft_strlen(*leftover));
		free(temp);
	}
	else
	{
		line = ft_substr(*leftover, 0, ft_strlen(*leftover));
		free(*leftover);
		*leftover = NULL;
	}
	return (line);
}

char	*free_join(char **line, char **end)
{
	char	*temp;

	temp = *line;
	*line = ft_strjoin(*line, *end);
	free (temp);
	free (*end);
	return (*line);
}
// free_join was needed to make make getline less than 26 lines

char	*getline(int fd, char **leftover)
{
	ssize_t	bytesread;
	char	buff[BUFFER_SIZE + 1];
	char	*line;
	char	*end;

	line = NULL;
	while (1)
	{
		if (!line)
			line = leftovercheck(leftover);
		else
		{
			end = leftovercheck(leftover);
			line = free_join(&line, &end);
		}		
		if (*leftover)
			return (line);
		bytesread = read(fd, buff, BUFFER_SIZE);
		if (bytesread == 0 && ft_strlen(line))
			return (line);
		if (bytesread <= 0)
			return (freeptr(&line));
		buff[bytesread] = 0;
		*leftover = ft_substr(buff, 0, bytesread);
	}
}

char	*get_next_line(int fd)
{
	static char	*leftover;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	if (!leftover)
	{
		leftover = (char *)malloc(1);
		if (!leftover)
			return (NULL);
		leftover[0] = 0;
	}
	return (getline(fd, &leftover));
}
