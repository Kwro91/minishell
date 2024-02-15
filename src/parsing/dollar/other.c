/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:47:05 by afontain          #+#    #+#             */
/*   Updated: 2024/02/15 16:40:21 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//change $x en "" (rien)
//les cas ou x est pas une lettre et les cas ou x n'existe pas dans env OU n'a pas de valeur
char	*dollar_left(t_command *cmd, int i)
{
	char	*str2;
	char	*str1;
	int		*j;

	j = i;
	if (getenv(cmd->line) == NULL || (getenv(cmd->line) != NULL && getenv(cmd->line[i+2]) == "\0" ))
	{
		while (cmd->line[i+1] != ' ')
			i++;
		str1 = ft_strdupuntil(cmd->line, j - 1);
		str2 = ft_strdupfrom(cmd->line, i);
		cmd->line = ft_strjoin(str1, str2);
		return (cmd->line);
	}
	i = j;
	else
	{
		if (ft_isalpha(cmd->line[i+1]) == 0)
			i++;
		str1 = ft_strdupuntil(cmd->line, j - 1);
		str2 = ft_strdupfrom(cmd->line, i);
		cmd->line = ft_strjoin(str1, str2);
		return (cmd->line);
	}
}

// char *dollar_env(t_command *cmd, int i)
