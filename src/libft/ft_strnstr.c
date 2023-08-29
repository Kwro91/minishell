/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:47:14 by besalort          #+#    #+#             */
/*   Updated: 2022/11/09 14:47:14 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (!src || !to_find)
		return (NULL);
	i = 0;
	if (ft_strlen(to_find) == 0)
		return ((char *)src);
	while (src[i] && i < len)
	{
		j = 0;
		while (src[i + j] == to_find[j] && src[i + j] && i + j < len)
		{
			if (to_find[j + 1] == '\0')
				return ((char *)&src[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
