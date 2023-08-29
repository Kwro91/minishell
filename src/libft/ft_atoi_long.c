/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:13:28 by besalort          #+#    #+#             */
/*   Updated: 2023/08/25 17:14:24 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atoi_long(const char	*str)
{
	int	        i;
	long int	nb;
	int	        signe;

	i = 0;
	nb = 0;
	signe = 1;
	if (str == NULL)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' ' && str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -signe;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * signe);
}
