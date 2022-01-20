/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmipa <sungmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 21:42:06 by sungmipa          #+#    #+#             */
/*   Updated: 2022/01/18 01:27:39 by sungmipa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strndup(char *src, int n)
{
	int		i;
	int		len;
	char	*dest;

	if (ft_strlen(src) < n || n == -1)
		len = ft_strlen(src);
	else
		len = n;
	dest = (char *)malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;
	
	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(&s[i]));
		i++;
	}
	if (c == 0)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin_m(char *s1, char *s2)
{
	int		i;
	int		s1_len;
	int		s2_len;
	char	*joined_str;

	if (s1 == NULL)
		return (ft_strndup(s2, -1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined_str = (char *)malloc(s1_len + s2_len + 1);
	if (joined_str == NULL)
		return (NULL);
	joined_str[s1_len + s2_len] = '\0';
	i = -1;
	while (++i < s1_len)
		joined_str[i] = s1[i];
	i = -1;
	while (++i <= s2_len)
		joined_str[s1_len + i] = s2[i];
	free(s1);
	return (joined_str);
}

void	file_node_free(f_list *lst, int fd)
{
	f_list	*prev;
	f_list	*cur;

	prev = NULL;
	cur = lst;
	while (cur)
	{
		if (cur -> fd == fd)
		{
			if (prev)
				prev -> next = cur -> next;
			free(cur);
			break;
		}
		prev = cur;
		cur = cur -> next;
	}
}

f_list	*get_file_node(int fd, f_list *lst)
{
	f_list			*prev;
	f_list			*cur;
	f_list			*new_file;
	
	prev = NULL;
	cur = lst;
	while (cur)
	{
		if (cur -> fd == fd)
			return(cur);
		prev = cur;
		cur = cur -> next;
	}
	new_file = (f_list *)malloc(sizeof(f_list));
	if (new_file == NULL) // !!!!!!!!!!!!동적할당 실패 예외처리!!!!!!!!!!!
		return (NULL);
	if (prev)
		prev -> next = new_file;
	new_file -> fd = fd;
	new_file -> remainder = NULL;
	new_file -> next = NULL;
	return (new_file);
}

char	*get_next_line(int fd)
{
	static f_list	*lst;
	f_list			*file_node;
	char			buf[BUFFER_SIZE + 1];
	char			*nl_ptr;
	char			*line;
	char			*tmp;
	int				read_flag;

	file_node = get_file_node(fd, lst);
	if (lst == NULL)
		lst = file_node;
	if (file_node -> remainder == NULL)	// 어떤 fd에도 남은 remainder가 없는경우.
		line = NULL;
	else
	{
		line = ft_strndup(file_node -> remainder, -1);
		if (line == NULL)
			return (NULL);
		free(file_node -> remainder);
		file_node -> remainder = NULL;
	}
	nl_ptr = ft_strchr(line, '\n');
	while (nl_ptr == NULL)
	{
		read_flag = read(fd, buf, BUFFER_SIZE);
		if(read_flag == 0)
		{
			if (lst == file_node)
			{
				lst = file_node -> next;
				free(file_node);
			}
			else
				file_node_free(lst, fd);
			return (line);
		}
		buf[read_flag] = '\0';
		line = ft_strjoin_m(line, buf);
		nl_ptr = ft_strchr(line, '\n');
	}
	// printf("gnl -> remainder : |%s|\n", nl_ptr + 1);
	// file_node -> remainder = ft_strndup(nl_ptr + 1, -1);
	if (*(nl_ptr + 1))
		file_node -> remainder = ft_strndup(nl_ptr + 1, -1);
	else
		file_node -> remainder = NULL;
	// printf("file_node -> remainder : |%s|\n", file_node -> remainder);
	tmp = line;
	line = ft_strndup(line, nl_ptr - line + 1);
	free(tmp);
	return (line);
}

// int main(void)
// {
// 	int		fd1;
// 	int		fd2;

// 	int		i;

// 	i = -1;
// 	fd1 = open("./exam.txt", O_RDONLY);
// 	// fd2 = open("./exam2.txt", O_RDONLY);
// 	printf("result : |%s|\n", get_next_line(fd1));
// 	printf("result : |%s|\n", get_next_line(fd1));
// 	printf("result : |%s|\n", get_next_line(fd1));
// 	printf("result : |%s|\n", get_next_line(fd1));
// 	printf("result : |%s|\n", get_next_line(fd1));
// 	printf("result : |%s|\n", get_next_line(fd1));
		
// 	// printf("%s", get_next_line(fd2));

// 	return (0);
// }