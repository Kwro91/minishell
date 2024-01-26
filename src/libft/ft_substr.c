/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:51:15 by besalort          #+#    #+#             */
/*   Updated: 2024/01/26 16:51:12 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*tab;

	if (!s)
		return (NULL);
	i = 0;
	if (start > ft_strlen(s) + 1)
	{
		tab = malloc(1);
		if (!tab)
			return (NULL);
		tab[0] = '\0';
		return (tab);
	}
	if (ft_strlen(&s[start]) <= len)
		tab = malloc(sizeof(char) * ft_strlen(&s[start]) + 1);
	else
		tab = malloc(len + 1);
	if (!tab)
		return (NULL);
	while (i < len && s[start])
		tab[i++] = s[start++];
	tab[i] = '\0';
	return (tab);
}
