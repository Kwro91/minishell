/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:25:20 by besalort          #+#    #+#             */
/*   Updated: 2024/03/22 16:53:52 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_arg(t_mdata *data, char *str, int *tab)
{
	int	count;
	int	i;
	count = count_cmd(data, str, " ");
	while (i < 4096 && tab[i] > -1)
		i++;
	i = i / 2;
	count += i;
	return (count);
}

void	split_tab(t_mdata *data, char *str, int *tab)
{
	char	**new;
	int		i;
	int		next;
	int		count;
	
	count = count_arg(data, str, tab);
	next = tab[0];
	while (cmd->line[i])
	{
		
	}
}