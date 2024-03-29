/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:16:15 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/06 11:51:46 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*copy(char *dest, char *src, size_t size)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[size + i] = src[i];
		i++;
	}
	dest[(size) + i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_size;
	size_t	s2_size;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (s1_size + s2_size + 1));
	if (result == NULL)
		return (write(2, "did not malloc\n", 15), NULL);
	copy(result, (char *)s1, 0);
	copy(result, (char *)s2, s1_size);
	result[s1_size + s2_size] = '\0';
	return (result);
}
