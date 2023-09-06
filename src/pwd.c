/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:11:42 by besalort          #+#    #+#             */
/*   Updated: 2023/09/06 13:42:56 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pwd(t_mdata *data, char **env)
{
    int		i;

    i = 0;
    while (ft_strncmp("PWD=", env[i], 4) != 0)
        i++;
    data->pwd = ft_strdup(env[i]+4);
}

void    pwd(t_mdata *data)
{
	ft_printf("%s\n", data->pwd);
}