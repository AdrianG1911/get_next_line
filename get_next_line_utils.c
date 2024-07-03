/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:37:02 by adrgutie          #+#    #+#             */
/*   Updated: 2024/06/23 16:37:17 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_ptr[i] = src_ptr[i];
		i++;
	}
	return (dst);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < dstsize)
		ft_memcpy(dst, src, srclen + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = 0;
	}
	return (srclen);
}

char	*free_ft_substr(char **s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;

	if (!(*s))
		return (NULL);
	slen = ft_strlen(*s);
	if (slen < start)
		len = 0;
	else if (len > slen)
		len = slen;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (freeptr(s, NULL, NULL), NULL);
	if (start >= slen)
		start = slen;
	if (slen - start < len)
		len = slen - start;
	ft_strlcpy(sub, (*s) + start, len + 1);
	return (sub);
}

char	*free_ft_strjoin(char **s1, char **s2)
{
	char	*newstr;
	size_t	s1len;
	size_t	s2len;

	if (!(*s1) || !(*s2))
		return (freeptr(s1, s2, NULL), NULL);
	s1len = ft_strlen(*s1);
	s2len = ft_strlen(*s2);
	newstr = (char *)malloc(s1len + s2len + 1);
	if (!newstr)
		return (freeptr(s1, s2, NULL), NULL);
	ft_strlcpy(newstr, *s1, s1len + 1);
	ft_strlcpy(newstr + s1len, *s2, s2len + 1);
	return (freeptr(s1, s2, NULL), newstr);
}
