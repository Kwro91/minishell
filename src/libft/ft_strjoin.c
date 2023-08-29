/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:02:48 by besalort          #+#    #+#             */
/*   Updated: 2022/11/28 14:50:46 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*tab;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	tab = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[j])
		tab[i++] = s1[j++];
	j = 0;
	while (s2[j])
		tab[i++] = s2[j++];
	tab[i] = '\0';
	return (tab);
}
