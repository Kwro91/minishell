/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:30:21 by besalort          #+#    #+#             */
/*   Updated: 2024/01/11 17:03:32 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lst	*createlist(int size, char **command)
{
	t_lst	*newlst;

	newlst = NULL;
	if (size > 0)
	{
		newlst = malloc(sizeof(t_lst));
		if (!newlst)
			return (NULL);
		newlst->cmd = command[0];
		newlst->command = ft_command(command[0]);
		newlst->next = createlist(size - 1, command + 1);
		if (newlst->next == NULL && (size -1) > 0)
			return (free(newlst), NULL);
	}
	return (newlst);
}
