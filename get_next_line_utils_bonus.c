/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmipa <sungmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 21:43:07 by sungmipa          #+#    #+#             */
/*   Updated: 2022/01/07 21:43:11 by sungmipa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// void	renew_remainder(char **remainder, int output_len, int fd)
// {
// 	char buf[BUFFER_SIZE + 1];

// 	if (!(*remainder) || output_len == ft_strlen(*remainder))
// 	{
// 		free(*remainder); 
// 		*remainder = ft_strndup("", 0);
// 	} // remainder에 개행 없음 -> 전부 line으로 전달, free(remainder), remainder = NULL;
// 	else
// 	{
// 		ft_memcpy(buf, (const char*)&(*remainder[output_len + 1]), ft_strlen(*remainder) - (output_len + 1));
// 		buf[ft_strlen(*remainder) - (output_len + 1)] = '\0';
// 		free(*remainder);
// 		*remainder = ft_strndup(buf, BUFFER_SIZE);
// 	}
// }

// char	*set_nl_from_remainder(f_list *remain_list, int fd)
// {
// 	int		output_len;
// 	char	*ret;
// 	char	*remainder;

// 	while (remain_list)
// 	{
// 		if (remain_list -> fd == fd)
// 			remainder = remain_list->remainder;
// 		else
// 			remain_list = remain_list->next;
// 	}
// 	output_len = 0;
// 	if (remainder)
// 	{
// 		while (remainder[output_len] && remainder[output_len] != '\n')
// 			output_len++;
// 		if (remainder[output_len] == '\0')
// 			ret = ft_strndup(remainder, ft_strlen(remainder));
// 		else
// 			ret = ft_strndup(remainder, output_len + 1);
// 		renew_remainder(remainder, output_len);
// 		if (remainder == NULL)
// 			return (NULL);
// 	}
// 	else
// 		ret = ft_strndup("", 0);
// 	return (ret);
// }
