/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungmipa <sungmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 21:43:07 by sungmipa          #+#    #+#             */
/*   Updated: 2022/01/07 21:43:11 by sungmipa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

	if (src[0] == '\0')
		return (NULL);
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
