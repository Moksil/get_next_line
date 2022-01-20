/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmipa <sungmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 21:43:23 by sungmipa          #+#    #+#             */
/*   Updated: 2022/01/07 21:48:42 by sungmipa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

//------------------------//
# include <fcntl.h>
# include <stdio.h>
//------------------------//

int		ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, int n);
char	*ft_strndup(char *src, int n);
char	*get_next_line(int fd);

#endif
