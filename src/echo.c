/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:08:19 by besalort          #+#    #+#             */
/*   Updated: 2023/09/06 13:41:10 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int nb_word(char **text)
{
    int	i;

	i = 0;
	while (text[i])
	{
		i++;
	}
	return (i);
}

void    ft_echo(char **text)
{
    int i;
	int	nb;
    
    i = 0;
	nb = nb_word(text);
    if (text && ft_strncmp(text[0], "-n\0", 3) == 0)
        i++;
    while (text[i])
    {
		if (i != nb-1)
        	write(1, text[i], ft_strlen(text[i]));
		else
			write(1, text[i], ft_strlen(text[i])-1);
        i++;
        if (text[i])
            write(1, " ", 1);
    }
    if (text && ft_strncmp(text[0], "-n\0", 3) != 0)
        write(1, "\n", 1);
    
}
