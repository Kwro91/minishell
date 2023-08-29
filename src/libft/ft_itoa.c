/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:40:48 by besalort          #+#    #+#             */
/*   Updated: 2022/11/23 14:57:50 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	howmany(long int nb)
{
	size_t	i;

	i = 1;
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i + 1);
}

static char	*revtab(char *tab)
{
	size_t	i;
	size_t	j;
	char	c;

	i = 0;
	j = ft_strlen((const char *)tab) - 1;
	if (tab[i] == '-')
		i++;
	while (i < j)
	{
		c = tab[i];
		tab[i++] = tab[j];
		tab[j--] = c;
	}
	return (tab);
}

char	*ft_itoa(int n)
{
	long int	nb;
	size_t		i;
	char		*tab;

	i = 0;
	nb = (long int)n;
	tab = malloc(sizeof(char) * howmany(nb));
	if (!tab)
		return (NULL);
	if (nb < 0)
	{
		tab[i++] = '-';
		nb = -nb;
	}
	while (nb > 9)
	{
		tab[i++] = nb % 10 + 48;
		nb /= 10;
	}
	tab[i++] = nb + 48;
	tab[i] = '\0';
	tab = revtab(tab);
	return (tab);
}
