/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adress.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:46:42 by besalort          #+#    #+#             */
/*   Updated: 2023/04/07 13:31:23 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_convertbase_a(unsigned long int nb)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (nb > 15)
	{
		count += ft_convertbase_a(nb / 16);
		count += ft_putchar_i(base[nb % 16]);
	}
	else
		count += ft_putchar_i(base[nb]);
	return (count);
}

int	ft_adress(void *p)
{
	int	count;

	count = 0;
	if (p == NULL)
		return (ft_putstr_i("(nil)"));
	else
	{
		count += ft_putstr_i("0x");
		count += ft_convertbase_a((unsigned long int)p);
	}
	return (count);
}
