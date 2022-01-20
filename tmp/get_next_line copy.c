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

char	*set_nl_from_remainder(char *remainder)
{
	int		output_len;
	char	*ret;

	// printf("passed prev remainder : |%s|\n", remainder);
	output_len = 0;
	if (remainder)
	{
		while (remainder[output_len] && remainder[output_len] != '\n')
			output_len++;
		if (remainder[output_len] == '\0')
			ret = ft_strndup(remainder, ft_strlen(remainder));
		else
			ret = ft_strndup(remainder, output_len + 1);
	}
	else
		ret = ft_strndup("", 0);
	return (ret);
}
/*
if malloc fail occured in get_nl_from_remainder(), -> return NULL; because ret is NULL
*/

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
	line = NULL;
	return (ret);
}

char	*get_next_line(int fd)
{
	int			i;
	int			read_num;
	char		buf[BUFFER_SIZE + 1];
	char		*ret;
	static char *remainder;

	if (fd == -1 || fd > 256)
		return (NULL);
	ret = set_nl_from_remainder(remainder);
	if (ret == NULL)
		return (NULL);
	// if (remainder)
	// 	printf("setted ret from remainder : |%s|, ft_strlen(ret) : %d, ft_strlen(remainder) : %d\n", ret, ft_strlen(ret), ft_strlen(remainder));
	if (!remainder || ft_strlen(ret) == ft_strlen(remainder))
	{
		free(remainder);
		remainder = ft_strndup("", 0);
		if (remainder == NULL)
			return (NULL);
	} // remainder에 개행 없음 -> 전부 line으로 전달, free(remainder), remainder = NULL;
	else
	{
		ft_memcpy(buf, (const char*)&remainder[ft_strlen(ret)], ft_strlen(remainder) - ft_strlen(ret));
		buf[ft_strlen(remainder) - ft_strlen(ret)] = '\0';
		free(remainder);
		remainder = ft_strndup(buf, BUFFER_SIZE);
		if (remainder == NULL)
			return (NULL);
		return (ret);
	}
	// printf("after renewed remainder : |%s|\n", remainder);
	read_num = read(fd, buf, BUFFER_SIZE);
	// printf("new read : |%s|\n", buf);
	if (read_num == 0 && ft_strlen(ret) == 0)
	{
		free(ret);
		ret = NULL;
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
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
				i++;
				while (buf[i] && i < read_num)
				{
					remainder = line_append_ch(remainder, buf[i]);
					if (remainder == NULL)
						return (NULL);
					i++;
				}
				buf[i] = '\0';
				// printf("remainder to next : |%s|\n", remainder);
				return (ret);
			}
			i++;
		}
		i = 0;
		read_num = read(fd ,buf, BUFFER_SIZE);
		// printf("new read : |%s|\n", buf);
	}
	// printf("remainder to next : |%s|\n", remainder);
	return (ret);
}

// int main()
// {
// 	int		i;
// 	int		fd;
// 	char	*line;

// 	fd = open("./exam.txt", O_RDONLY);
// 	i = 0;
// 	while (i < 2)
// 	{
// 		printf("\n========== %d try ==========\n", i + 1);
// 		line = get_next_line(fd);
// 		printf("\n*=====*\n|%s|*=====*\n", line);
// 		printf("line length : %d\n", ft_strlen(line));
// 		printf("\n============================\n");
// 		i++;
// 	}
// 	return (0); 
// }
 