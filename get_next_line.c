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

// #define BUFFER_SIZE 1

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
	free(line);
	return (ret);
}

char	*get_next_line(int fd)
{
	int			i;
	int			read_num;
	char		*buf;
	char		*ret;
	static char *remainder;

	ret = (char *)malloc(1);
	if (ret == NULL)
		return (NULL);
	if (remainder == 0)
	{
		remainder = (char *)malloc(1);
		if (remainder == NULL)
			return (NULL);
		remainder[0] = '\0';
	}
	else
	{
		i = 0;
		while (*remainder && *remainder != '\n')
		{
			ret = line_append_ch(ret, *remainder);
			remainder++;
		}
	}
	buf = (char *)malloc(BUFFER_SIZE);
	if (buf == NULL)
		return (NULL);
	read_num = read(fd, buf, BUFFER_SIZE);
	i = 0;
	while (read_num)
	{
		while (i < read_num)
		{
			ret = line_append_ch(ret, buf[i]);
			if (ret == NULL)
				return (NULL);
			if (buf[i] == '\n')
			{
				free(remainder);
				remainder = (char *)malloc(BUFFER_SIZE - i);
				if (remainder == NULL)
					return (NULL);
				ft_memcpy(remainder, &buf[i + 1], BUFFER_SIZE - i - 1);
				remainder[BUFFER_SIZE - i] = '\0';
				return (ret);
			}
			i++;
		}
		i = 0;
		read_num = read(fd ,buf, BUFFER_SIZE);
	}
	return (ret);
}

int main()
{
	int		fd;
	int		read_num;
	char	*buf;
	char	*line;

	buf = (char *)malloc(3);
	fd = open("./exam.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	return (0); 
}
 
 