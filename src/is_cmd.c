/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:26:03 by besalort          #+#    #+#             */
/*   Updated: 2023/09/06 11:54:08 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_echo(char **cmd_total)
{
    char *name;
    
    name = "echo\0";
    if (ft_strncmp(name, cmd_total[0], 5) == 0)
    {
        ft_echo(&cmd_total[1]);
        return (1);
    }
    return (0);
}