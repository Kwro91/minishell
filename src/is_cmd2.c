/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:01:29 by afontain          #+#    #+#             */
/*   Updated: 2023/11/30 17:19:29 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_unset(char **cmd_total, t_mdata *data)
{
	char    *name0;
    char    *namen;
    
    name0 = "unset\0";
    namen = "unset\n\0";
    if (ft_strncmp(name0, cmd_total[0], 6) == 0 || ft_strncmp(namen, cmd_total[0], 7) == 0)
    {
        ft_unset(cmd_total, data);
        return (1);
    }
    return (-1);
}
