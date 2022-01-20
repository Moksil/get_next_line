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

int	has_newline(char *str)
{
	int	idx;

	idx = 0;
	while(str[idx] && str[idx]!= '\n')
		idx++;
	if (str[idx] == '\n')
		return (idx);
	else
		return (-1);
}

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

	if (ft_strlen(src) < n)
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

// char	*ft_lstclear(f_list **lst)
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
// 	return (NULL);
// }

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

char	*renew_remainder(char **r_ptr)
{
	char	*ret;
	char	*tmp;
	char	*nl_ptr;
	int		nl_idx;

	// nl_ptr = ft_strchr(*r_ptr, '\n');
	nl_idx = has_newline(*r_ptr);

	// if (nl_ptr == NULL)
	if (nl_idx == -1)
	{
		ret = ft_strndup(*r_ptr, BUFFER_SIZE);
		*r_ptr = ft_strndup("", 0);
	}
	else
	{
		// ret = ft_strndup(*r_ptr, nl_ptr - *r_ptr + 1);
		ret = ft_strndup(*r_ptr, nl_idx + 1);
		tmp = *r_ptr;
		// *r_ptr = ft_strndup(nl_ptr + 1, BUFFER_SIZE);
		*r_ptr = ft_strndup(&(*r_ptr[nl_idx + 1]), BUFFER_SIZE);
		free(tmp);
		tmp = NULL;
	}
	if (*r_ptr == NULL)
		return (NULL);
	return (ret);
}

// char	*get_line_and_remain(f_list *lst, int fd, char *line, char *nl_ptr)
char	*get_line_and_remain(f_list *lst, int fd, char *line, int nl_idx)
{
	f_list	*cur;
	char	*ret;
	char	*tmp;

	cur = lst;
	while (cur)
	{
		if (cur -> fd == fd)
			break;
		cur = cur -> next;
	}
	//line에서 nl_ptr포함하여 앞부분은 return, 뒷부분은 remainder에 저장.
	ret = ft_strndup(line, nl_idx + 1);
	tmp = line;
	// cur ->remainder = ft_strndup(nl_ptr + 1, BUFFER_SIZE);
	cur ->remainder = ft_strndup(&(cur -> remainder[nl_idx + 1]), BUFFER_SIZE);
	free(tmp);
	tmp = NULL;
	return (ret);
}

char	*get_remainder_from_line(f_list *lst, int fd)
{
	f_list	*prev;
	f_list	*cur;
	f_list	*new_file;

	prev = NULL;
	cur = lst;
	while (cur)
	{
		if (cur -> fd == fd)
			return(renew_remainder(&(cur -> remainder)));
		prev = cur;
		cur = cur -> next;
	}
	new_file = (f_list *)malloc(sizeof(f_list));
	if (new_file == NULL)
		return (NULL);
	if (prev)
		prev -> next = new_file;
	else
		lst = new_file;
	new_file -> fd = fd;
	new_file -> remainder = ft_strndup("", 0);
	new_file -> next = NULL;
	return (new_file -> remainder);
}

char	**get_remainder_ptr(int fd)
{
	static f_list	*lst;
	f_list	*prev;
	f_list	*cur;
	f_list	*new_file;
	
	prev = NULL;
	cur = lst;
	while (cur)
	{
		if (cur -> fd == fd)
			return(&(cur -> remainder));
		prev = cur;
		cur = cur -> next;
	}
	new_file = (f_list *)malloc(sizeof(f_list));
	if (new_file == NULL)
		return (NULL);
	if (prev)
		prev -> next = new_file;
	else
		lst = new_file;
	new_file -> fd = fd;
	new_file -> remainder = ft_strndup("", 0);
	new_file -> next = NULL;
	return (&(new_file -> remainder));
}


char	*get_next_line(int fd)
{
	char			*ret;
	char			**r_ptr;
	char			buf[BUFFER_SIZE + 1];
	int				nl_idx;
	int				read_flag;
	// char			*nl_ptr;

	ret = renew_remainder(get_remainder_ptr(fd));
	if (ret == NULL)
		return (NULL);
	// printf("remainder : %s\n", "");
	// nl_ptr = ft_strchr(ret, '\n');
	nl_idx = has_newline(ret);
	// if (nl_ptr)
	if (nl_idx >= 0)
		return (ret);
	// while (nl_ptr == NULL) // remainder에 newline 없을 때
	while (nl_idx == -1) // remainder에 newline 없을 때
	{
		read_flag = read(fd, buf, BUFFER_SIZE);
		if (read_flag == 0)
			return (ret);
		ret = ft_strjoin_m(ret, buf);
		// nl_ptr = ft_strchr(ret, '\n');
		nl_idx = has_newline(ret);
	}
	// ret에 \n을 포함한 문자열이 저장되어있음.
	// remainder_ptr에 \n뒷부분 저장해주고 ret에 앞부분 가져와야함.

	// ret = get_line_and_remain(lst, fd, ret, nl_ptr);
	r_ptr = get_remainder_ptr(fd);
	*r_ptr = ret;
	ret = renew_remainder(r_ptr);
	//buf에 newline 있으면 newline까지 ret에 붙이고 나머지 remainder로
	//buf에 newline 없으면 newline이 있거나 i가 0일때까지 read해서 ret에 붙이기.
	// remainder에 newline 있을 때
	return (ret); // f_list clear 어떻게?
}


int main(void)
{
	int		fd;

	fd = open("./exam.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
}