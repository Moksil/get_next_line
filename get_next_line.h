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

//------------------------//
# include <fcntl.h>
# include <stdio.h>
//------------------------//

typedef struct file_list
{
	int					fd;
	char				*remainder;
	struct file_list	*next;
}						f_list;

int		ft_strlen(const char *s);
char	*ft_strndup(char *src, int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_m(char *s1, char *s2);
void	ft_lstclear(f_list **lst);
char	*split_line_and_remainder(f_list *f_dptr);
char	**get_remainder_ptr(int fd);
char	*get_next_line(int fd);

#endif