/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:36:10 by besalort          #+#    #+#             */
/*   Updated: 2023/04/07 13:31:31 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	whatisit(char c, va_list b)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar_i((char)va_arg(b, int));
	else if (c == 's')
		count += ft_putstr_i(va_arg(b, char *));
	else if (c == 'i' || c == 'd')
		count += ft_putnbr_i(va_arg(b, int));
	else if (c == 'u')
		count += ft_putnbr_u(va_arg(b, unsigned int));
	else if (c == 'x')
		count += ft_convertbase(va_arg(b, unsigned int), 0);
	else if (c == 'X')
		count += ft_convertbase(va_arg(b, unsigned int), 1);
	else if (c == '%')
		count += ft_putchar_i('%');
	else if (c == 'p')
		count += ft_adress(va_arg(b, void *));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	size_t	i;
	int		count;
	va_list	b;

	i = 0;
	count = 0;
	va_start(b, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += whatisit(str[i + 1], b);
			i += 2;
		}
		else
		{
			count += ft_putchar_i(str[i]);
			i++;
		}
	}
	va_end(b);
	return (count);
}
