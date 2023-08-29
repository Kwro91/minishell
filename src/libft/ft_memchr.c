/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:42:13 by besalort          #+#    #+#             */
/*   Updated: 2022/11/28 14:43:18 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int to_find, size_t size)
{
	size_t			i;
	unsigned char	*new_src;

	i = 0;
	new_src = (unsigned char *)src;
	while (i < size)
	{
		if (new_src[i] == (unsigned char)to_find)
			return ((void *)new_src + i);
		i++;
	}
	return (NULL);
}
