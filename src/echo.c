/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:08:19 by besalort          #+#    #+#             */
/*   Updated: 2023/08/29 15:08:04 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_echo(char **text)
{
    int i;
    
    i = 0;
    if (text && ft_strncmp(text[0], "-n\0", 3) == 0)
        i++;
    while (text[i])
    {
        write(1, text[i], ft_strlen(text[i]));
        i++;
        if (text[i])
            write(1, " ", 1);
    }
    if (text && ft_strncmp(text[0], "-n\0", 3) != 0)
        write(1, "\n", 1);
    
}

int main(int ac, char **av)
{
    (void)ac;
        ft_echo(&av[1]);
}