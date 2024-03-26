/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:49:05 by afontain          #+#    #+#             */
/*   Updated: 2024/03/26 16:02:41 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_squote(t_mdata *data, t_command *cmd, int i)
{
	int	len;

	len = ft_strlen(cmd->line);
	while (i < len && cmd->line)
	{
		if (cmd->line[i] == '\'')
			return (i);
		i++;
		len = ft_strlen(cmd->line);
	}
	cmd->good = -1;
	data->block = 1;
	return (ft_error(data, "Error: simple quote not closed\n", 2), -2);
}
