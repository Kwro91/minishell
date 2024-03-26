/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:03:32 by afontain          #+#    #+#             */
/*   Updated: 2024/03/26 16:02:46 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_files_names(t_mdata *data)
{
	t_command	*tmp;
	int			ok;

	ok = 0;
	tmp = data->cmd;
	while (tmp && ok == 0)
	{
		if (tmp->good == -1)
			ok = -1;
		if (ok == 0)
			sub_files(data, tmp);
		tmp = tmp->next;
	}
}

int	parse_dquote(t_mdata *data, t_command *cmd, int i)
{
	int	len;

	len = ft_strlen(cmd->line);
	while (i < len && cmd->line)
	{
		if (cmd->line[i] == '"')
			return (i);
		else if (cmd->line[i] == '$')
			i = handle_dollar(data, cmd, i);
		i++;
		len = ft_strlen(cmd->line);
	}
	cmd->good = -1;
	data->block = 1;
	return (ft_error(data, "Error: double quote not closed\n", 2), -2);
}
