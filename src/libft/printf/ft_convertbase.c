/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convertbase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:45:35 by besalort          #+#    #+#             */
/*   Updated: 2023/04/07 13:31:14 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convertbase(unsigned int nb, int up)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (up == 1)
		base = "0123456789ABCDEF";
	if (nb > 15)
	{
		count += ft_convertbase(nb / 16, up);
		count += ft_putchar_i(base[nb % 16]);
	}
	else
		count += ft_putchar_i(base[nb]);
	return (count);
}
