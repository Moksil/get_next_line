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
void	fd_eof(f_list *lst, int fd)
{
	f_list	*prev;
	f_list	*cur;

	prev = NULL;
	cur = lst;
	while(cur)
	{
		if (cur -> fd == fd)
		{
			free(cur->remainder);
			if (!prev)
				lst = cur -> next;
			else
				prev -> next = cur -> next;
			free(cur);
			break;
		}
		prev = cur;
		cur = cur -> next;
	}
}
void	clear_lst(f_list *lst)
{
	f_list	*prev;
	f_list	*cur;

	prev = NULL;
	cur = lst;
	while(cur)
	{
		free(prev);
		free(cur->remainder);
		prev = cur;
		cur = cur -> next;
	}
	free(prev);
}

char	*renew_remainder(f_list *fd_node)
{
	int		i;
	char	*ret;
	char	buf[BUFFER_SIZE + 1];

	i = 0;
	while(fd_node -> remainder[i] && fd_node -> remainder[i] != '\n')
		i++;
	if (!fd_node -> remainder[i])
	{
		ret = ft_strndup(fd_node -> remainder, BUFFER_SIZE);
		free(fd_node -> remainder); 
		fd_node -> remainder = ft_strndup("", 0);
	} // remainder에 개행 없음 -> 전부 line으로 전달, free(remainder), remainder = NULL;
	else
	{
		ret = ft_strndup(fd_node -> remainder, i + 1);
		ft_memcpy(buf, (const char*)&(fd_node -> remainder)[i + 1], ft_strlen(fd_node -> remainder) - (i + 1));
		buf[ft_strlen(fd_node -> remainder) - (i + 1)] = '\0';
		free(fd_node -> remainder);
		fd_node -> remainder = ft_strndup(buf, BUFFER_SIZE);
	}
	if (fd_node -> remainder == NULL)
		return (NULL);
	return (ret);
}

f_list	*get_remainder_from_list(f_list *lst, int fd)
{
	f_list	*cur;
	f_list	*prev;
	f_list	*new_node;

	prev = NULL;
	cur = lst;
	while (cur)
	{
		if (cur -> fd == fd)
			return (cur);
		prev = cur;
		cur = cur -> next;
	}
	new_node = (f_list *)malloc(sizeof(f_list));
	if (new_node == NULL)
		return (NULL);
	if (prev)
		prev -> next = new_node;
	cur = new_node;
	cur -> fd = fd;
	cur -> remainder = ft_strndup("", 0);
	cur -> next = NULL;
	return (cur);
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
	int				i;
	int				read_num;
	char			buf[BUFFER_SIZE + 1];
	char			*ret;
	static f_list	*lst;

	if (fd == -1 || fd > 256)
		return (NULL);
	ret = renew_remainder(get_remainder_from_list(lst, fd));
	if (ret == NULL)
		return (NULL);
	// if (remainder)
	// 	printf("setted ret from remainder : |%s|, ft_strlen(ret) : %d, ft_strlen(remainder) : %d\n", ret, ft_strlen(ret), ft_strlen(remainder));
	// remainder에 개행 없음 -> 전부 line으로 전달, free(remainder), remainder = NULL;
	// printf("after renewed remainder : |%s|\n", remainder);
	read_num = read(fd, buf, BUFFER_SIZE);
	// printf("new read : |%s|\n", buf);
	if (read_num == 0 && ft_strlen(ret) == 0)
	{
		free(ret);
		ret = NULL;
		fd_eof(lst, fd);
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
 