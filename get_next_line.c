/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmipa <sungmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 21:42:06 by sungmipa          #+#    #+#             */
/*   Updated: 2022/01/07 21:49:14 by sungmipa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

#define BUFFER_SIZE 1

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, int n)
{
	int					i;
	unsigned char		*dptr;
	const unsigned char	*sptr;

	if (!dest && !src)
		return (NULL);
	i = 0;
	dptr = dest;
	sptr = src;
	while (i < n)
	{
		dptr[i] = sptr[i];
		i++;
	}
	return (dest);
}


char	*line_append_ch(char* line, char ch)
{
	char	*ret;
	int		line_len;

	line_len = ft_strlen(line);
	ret = (char *)malloc(line_len + 2);
	if (ret == NULL)
		return (NULL);
	ft_memcpy(ret, line, line_len);
	ret[line_len] = ch;
	ret[line_len + 1] = '\0';
	if (line_len != 0)
		free(line);
	return (ret);
}

char	*get_next_line(int fd)
{
	int		i;
	int		idx;
	char	*buf;
	char	*ret;

	buf = (char *)malloc(BUFFER_SIZE);
	if (buf == NULL)
		return (NULL);
	read(fd, buf, BUFFER_SIZE);
	i = 0;
	ret = "";
	while (1)
	{
		if (i == BUFFER_SIZE)
		{
			free(buf);
			buf = (char *)malloc(BUFFER_SIZE);
			if (buf == NULL)
				return (NULL);
			i -= BUFFER_SIZE;
			read(fd, buf, BUFFER_SIZE);
		}
		if (buf[i] == '\n')
		{
			ret = line_append_ch(ret, buf[i]);
			if (ret == NULL)
				return (NULL);
			break ;
		}
		else
		{
			ret = line_append_ch(ret, buf[i]);
			if (ret == NULL)
				return (NULL);
		}
		i++;
	}
	return (ret);
}

int main()
{
	printf("%s\n", get_next_line(0));
	return (0);
}
 