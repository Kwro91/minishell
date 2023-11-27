/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:14:52 by besalort          #+#    #+#             */
/*   Updated: 2023/11/27 15:15:30 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_free_lines(char	**lines)
{
    int i;
    
    i = 0;
	if (!lines)
		return ;
    while (lines[i])
    {
        free(lines[i]);
        i++;
    }
    free(lines);
}

void    ft_free_mini(t_mdata *data)
{
    ft_free_lines(data->env);
    ft_free_lines(data->paths);
    free(data->pwd);
	rl_clear_history();
}