/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:14:52 by besalort          #+#    #+#             */
/*   Updated: 2023/09/08 16:09:28 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_free_menv(t_mdata *data)
{
    int i;
    
    i = 0;
    while (data->env[i])
    {
        free(data->env[i]);
        i++;
    }
    free(data->env);
}

void    ft_free_mpaths(t_mdata *data)
{
    int i;
    
    i = 0;
    while (data->paths[i])
    {
        free(data->paths[i]);
        i++;
    }
    free(data->paths);
}

void    ft_free_mini(t_mdata *data)
{
    ft_free_menv(data);
    ft_free_mpaths(data);
    free(data->pwd);
}