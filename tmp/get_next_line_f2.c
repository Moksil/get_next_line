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

// void	ft_lstclear(f_list **lst)
// {
// 	f_list	*cur;
// 	f_list	*tmp;

// 	cur = *lst;
// 	while (cur)
// 	{
// 		tmp = cur;
// 		cur = cur -> next;
// 		free(tmp -> remainder);
// 		free(tmp);
// 		tmp = NULL;
// 	}
// 	*lst = NULL;
// }

char	*split_line_and_remainder(f_list *f_dptr)
{
	char	*line;
	char	*tmp;
	char	*nl_ptr;

	nl_ptr = ft_strchr(f_dptr -> remainder, '\n');
	if (nl_ptr == NULL)
	{
		line = ft_strndup(f_dptr -> remainder, -1);
		free(f_dptr -> remainder);
		f_dptr -> remainder = NULL;
	}
	else
	{
		line = ft_strndup(f_dptr -> remainder, nl_ptr - (f_dptr -> remainder + 1));
		tmp = f_dptr -> remainder;
		f_dptr -> remainder = ft_strndup(nl_ptr + 1, -1);
		free(tmp);
		tmp = NULL;
	}
	if (f_dptr -> remainder == NULL)
		return (NULL);
	return (line);
}

f_list	*get_node_ptr(int fd)
{
	static f_list	**lst;
	f_list			**prev;
	f_list			**cur;
	f_list			*new_file;
	
	prev = NULL;
	cur = lst;
	while (cur)
	{
		if ((*cur) -> fd == fd)
			return(*cur);
		prev = cur;
		(*cur) = (*cur) -> next;
	}
	new_file = (f_list *)malloc(sizeof(f_list));
	if (new_file == NULL)
		return (NULL);
	if (prev)
		(*prev) -> next = new_file;
	else
		(*lst) = new_file;
	new_file -> fd = fd;
	new_file -> remainder = ft_strndup("", 0);
	new_file -> next = NULL;
	return (*lst);
}
/* char **get_remainder_ptr(int fd)
this fuction has static f_list * lst
lst handle fd and fd's remainder
Only can this function access to static list - lst

this function returns int param address of fd's remainder
1) if first call of fd
static f_list lst make new node of new fd and returns empty string like ""
2) lst aleady has fd's Node
It returns address of char pointer remainder (char **)
*/

char	*get_next_line(int fd)
{
	f_list	*f_dptr;
	char	*nl_ptr;
	char	*line;
	char	*tmp;
	char	buf[BUFFER_SIZE + 1];
	int		read_flag;

	printf("11111");
	f_dptr = get_node_ptr(fd);
	line = split_line_and_remainder(f_dptr);
	// printf("- %d call - \nline from remainder : |%s|\n", call_flag + 1, line);
	// printf("line : |%s|\n", line);
	if (line == NULL)
		return (NULL);
	nl_ptr = ft_strchr(line, '\n');
	if (nl_ptr)			// remainder에서 가져온 line에 newline이 존재할 경우.
		return (line); 	// 이미 newline 이후를 remainder에 보관했음. 바로 line return
	while (!nl_ptr)		// 이하 코드가 실행된다는건 remainder가 비어있다는 것.
	{
		read_flag = read(fd, buf, BUFFER_SIZE);
		if (read_flag == 0)
			return (line);
		buf[read_flag] = '\0';
		line = ft_strjoin_m(line, buf);
		nl_ptr = ft_strchr(line, '\n');
	}	// line에 newline이 존재할때까지 buf에서 읽은 값을 line 뒤에 붙임 / newline 이후 값을 다시 remainder에 보내줘야함.
	free(f_dptr -> remainder);
	f_dptr -> remainder = ft_strndup(nl_ptr + 1, BUFFER_SIZE);
	tmp = line;
	line = ft_strndup(line, nl_ptr - line + 1);
	free(tmp);
	// printf("length of result : %d\n", ft_strlen(line));
	return (line);
}

int main(void)
{
	int		fd1;
	int		fd2;

	int		i;

	i = -1;
	fd1 = open("./exam.txt", O_RDONLY);
	// fd2 = open("./exam2.txt", O_RDONLY);
	while(++i < 10)
		printf("result : |%s|\n", get_next_line(fd1));
		
	// printf("%s", get_next_line(fd2));

	return (0);
}