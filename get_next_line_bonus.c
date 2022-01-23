/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmipa <sungmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 21:42:06 by sungmipa          #+#    #+#             */
/*   Updated: 2022/01/18 01:27:39 by sungmipa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_list	*file_node_free(t_list *lst, int fd)
{
	t_list	*prev;
	t_list	*cur;

	prev = NULL;
	cur = lst;
	while (cur)
	{
		if (cur->fd == fd)
		{
			if (prev)
				prev->next = cur->next;
			else
			{
				prev = cur;
				cur = cur -> next;
				free(prev);
				return (cur);
			}
			free(cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
	return (prev);
}

static t_list	*get_file_node(int fd, t_list *lst)
{
	t_list			*prev;
	t_list			*cur;
	t_list			*new_file;

	if (fd > FD_MAX || fd < 0)
		return (NULL);
	prev = NULL;
	cur = lst;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		prev = cur;
		cur = cur->next;
	}
	new_file = (t_list *)malloc(sizeof(t_list));
	if (new_file == NULL)
		return (NULL);
	if (prev)
		prev->next = new_file;
	new_file->fd = fd;
	new_file->remainder = NULL;
	new_file->next = NULL;
	return (new_file);
}

static char	*get_line_from_remainder(t_list *file_node)
{
	char	*line;

	if (file_node->remainder == NULL)
		line = NULL;
	else
	{
		line = ft_strndup(file_node->remainder, -1);
		if (line == NULL)
			return (NULL);
		free(file_node->remainder);
		file_node->remainder = NULL;
	}
	return (line);
}

static char	*read_and_remain(t_list *lst, char *line, int *flag, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*nl_ptr;
	char	*tmp;

	nl_ptr = ft_strchr(line, '\n');
	while (nl_ptr == NULL)
	{
		*flag = read(fd, buf, BUFFER_SIZE);
		if (*flag == 0 || *flag == -1)
			return (line);
		buf[*flag] = '\0';
		line = ft_strjoin_m(line, buf);
		nl_ptr = ft_strchr(line, '\n');
	}
	(get_file_node(fd, lst)->remainder) = ft_strndup(nl_ptr + 1, -1);
	tmp = line;
	line = ft_strndup(line, nl_ptr - line + 1);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	t_list			*file_node;
	char			*line;
	int				flag;

	file_node = get_file_node(fd, lst);
	if (file_node == NULL)
		return (NULL);
	if (lst == NULL)
		lst = file_node;
	flag = 1;
	line = get_line_from_remainder(file_node);
	line = read_and_remain(lst, line, &flag, fd);
	if (flag <= 0)
	{
		if (lst == get_file_node(fd, lst))
			lst = file_node_free(lst, fd);
		else
			file_node_free(lst, fd);
		if (flag == -1)
			return (NULL);
	}
	if (!line && !(file_node->remainder))
		return (NULL);
	return (line);
}
