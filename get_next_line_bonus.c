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

static void	file_node_free(t_list *lst, int fd)
{
	t_list	*prev;
	t_list	*cur;

	prev = NULL;
	cur = lst;
	while (cur)
	{
		if (cur -> fd == fd)
		{
			if (prev)
				prev -> next = cur -> next;
			free(cur);
			break ;
		}
		prev = cur;
		cur = cur -> next;
	}
}

static t_list	*get_file_node(int fd, t_list *lst)
{
	t_list			*prev;
	t_list			*cur;
	t_list			*new_file;

	prev = NULL;
	cur = lst;
	while (cur)
	{
		if (cur -> fd == fd)
			return (cur);
		prev = cur;
		cur = cur -> next;
	}
	new_file = (t_list *)malloc(sizeof(t_list));
	if (new_file == NULL)
		return (NULL);
	if (prev)
		prev -> next = new_file;
	new_file -> fd = fd;
	new_file -> remainder = NULL;
	new_file -> next = NULL;
	return (new_file);
}

static char	*get_line_from_remainder(t_list *file_node)
{
	char	*line;

	if (file_node -> remainder == NULL)
		line = NULL;
	else
	{
		line = ft_strndup(file_node -> remainder, -1);
		if (line == NULL)
			return (NULL);
		free(file_node -> remainder);
		file_node -> remainder = NULL;
	}
	return (line);
}

static char	*read_and_remain(t_list *lst, char *line, int *flag, int fd)
{
	t_list	*s_file_list;
	char	buf[BUFFER_SIZE + 1];
	char	*nl_ptr;

	s_file_list = get_file_node(fd, lst);
	nl_ptr = ft_strchr(line, '\n');
	while (nl_ptr == NULL)
	{
		*flag = read(fd, buf, BUFFER_SIZE);
		if (*flag == 0 || *flag == -1)
		{
			if (*flag == -1 || (*flag == 0 && lst == s_file_list))
				*flag -= 1;
			else
				*flag = 0;
			return (line);
		}
		buf[*flag] = '\0';
		line = ft_strjoin_m(line, buf);
		nl_ptr = ft_strchr(line, '\n');
	}
	s_file_list -> remainder = ft_strndup(nl_ptr + 1, -1);
	line = ft_strndup(line, nl_ptr - line + 1);
	free(nl_ptr - ft_strlen(line) + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	t_list			*file_node;
	char			*line;
	int				flag;

	if (fd > FD_MAX || fd < 0)
		return (NULL);
	file_node = get_file_node(fd, lst);
	if (file_node == NULL)
		return (NULL);
	if (lst == NULL)
		lst = file_node;
	line = get_line_from_remainder(file_node);
	line = read_and_remain(lst, line, &flag, fd);
	if (flag <= -1)
	{
		lst = file_node -> next;
		free(file_node);
		if (flag == -2)
			return (NULL);
	}
	else if (flag == 0)
		file_node_free(lst, fd);
	return (line);
}
