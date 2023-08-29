/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:43:39 by besalort          #+#    #+#             */
/*   Updated: 2023/04/07 13:31:48 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_i(char *str)
{
	int	i;

	i = 0;
	if (!str)
		i += write (1, "(null)", 6);
	else
		while (str[i])
			write (1, &str[i++], 1);
	return (i);
}
