/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:14:10 by besalort          #+#    #+#             */
/*   Updated: 2024/02/16 19:31:57 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_vdollar(t_mdata *data, t_command *cmd, int i, int len)
{
	char	*start;
	char	*end;

	start = ft_strdupuntil(data, cmd->line, i);
	end = ft_strdup(&cmd->line[i + len]);
	if (start)
	{
		ft_free_me(cmd->line);
		if (!end)
			cmd->line = start;
		else
		{
			cmd->line = ft_strjoin(start, end);
			if (!cmd->line)
				ft_error(data, "Error: malloc\n", 1);
		}
	}
	else
	{
		ft_free_me(cmd->line);
		cmd->line = "";
	}
}