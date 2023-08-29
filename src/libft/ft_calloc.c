/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:38:18 by besalort          #+#    #+#             */
/*   Updated: 2023/03/29 15:14:03 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;
	size_t	total;

	total = nmemb * size;
	if (nmemb && nmemb * size / nmemb != size)
		return (NULL);
	tab = malloc(sizeof(void) * total);
	if (!tab)
		return (NULL);
	ft_bzero(tab, total);
	return (tab);
}
