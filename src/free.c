/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:14:52 by besalort          #+#    #+#             */
/*   Updated: 2023/11/30 15:29:39 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_adr(void *adr)
{
	if (adr)
		free(adr);
	adr = NULL;
}

void    ft_free_lines(char	**lines)
{
    int i;
    
    i = 0;
	if (lines == NULL)
		return ;
    while (lines && lines[i])
    {
        free(lines[i]);
        i++;
    }
    free(lines);
}

void    ft_free_mini(t_mdata *data)
{
	if (data->env != NULL)
    	ft_free_lines(data->env);
    ft_free_lines(data->paths);
    free(data->pwd);
	rl_clear_history();
}