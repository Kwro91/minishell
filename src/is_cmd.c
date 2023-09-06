/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:26:03 by besalort          #+#    #+#             */
/*   Updated: 2023/09/06 18:06:46 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_echo(char **cmd_total)
{
    char    *name0;
    char    *namen;
    
    name0 = "echo\0";
    namen = "echo\n\0";
    if (ft_strncmp(name0, cmd_total[0], 5) == 0 || ft_strncmp(namen, cmd_total[0], 6) == 0)
    {
        ft_echo(&cmd_total[1]);
        return (1);
    }
    return (-1);
}

int is_pwd(char **cmd_total, t_mdata *data)
{
    char    *name0;
    char    *namen;
    
    name0 = "pwd\0";
    namen = "pwd\n\0";
    if (ft_strncmp(name0, cmd_total[0], 4) == 0 || ft_strncmp(namen, cmd_total[0], 5) == 0)
    {
        pwd(data);
        return (1);
    }
    return (-1);
}

int is_exit(char **cmd_total, t_mdata *data)
{
    char    *name0;
    char    *namen;
    
    name0 = "exit\0";
    namen = "exit\n\0";
    if (ft_strncmp(name0, cmd_total[0], 5) == 0 || ft_strncmp(namen, cmd_total[0], 6) == 0)
    {
        exit_mini(data);
        return (1);
    }
    return (-1);
}