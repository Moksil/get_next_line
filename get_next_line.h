/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmipa <sungmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 21:43:23 by sungmipa          #+#    #+#             */
/*   Updated: 2022/01/07 21:48:42 by sungmipa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define FD_MAX	256

typedef struct s_file_list
{
	int					fd;
	char				*remainder;
	struct s_file_list	*next;
}						t_list;

int		ft_strlen(const char *s);
char	*ft_strndup(char *src, int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_m(char *s1, char *s2);
char	*get_next_line(int fd);

#endif