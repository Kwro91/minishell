/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:47:05 by afontain          #+#    #+#             */
/*   Updated: 2024/02/18 22:14:22 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//change $x en "" (rien)
//les cas ou x est pas une lettre et les cas ou x n'existe pas dans env OU n'a pas de valeur
int	dollar_left(t_mdata *data, t_command *cmd, int i)
{
	char	*start;
	char	*end;

	if (cmd->line[i + 1] == '\0') //cas $\0
		return (i);
	else if (cmd->line[i + 2] != '\0') //cas $4coucou
	{
		start = ft_strdupuntil(data, cmd->line, i - 1);
		end = ft_strdup(&cmd->line[i + 2]);
		ft_free_me(cmd->line);
		cmd->line = ft_strjoin(start, end);
		ft_free_me(start);
		ft_free_me(end);
		return (i - 1);
	}
	return (-2);
}
