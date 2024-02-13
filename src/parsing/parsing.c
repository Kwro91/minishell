/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:30:01 by besalort          #+#    #+#             */
/*   Updated: 2024/02/13 17:58:03 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_dquote(t_mdata *data, t_command *cmd, char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '"')
			return (i);
		else if (line[i] == '$')
			ft_printf("DETECTION D'UN $ DANS UNE DQUOTE\n");
		i++;
	}
	cmd->good = -1;
	return (ft_error(data, "Error: double quote not closed\n", 0), -1);
}

int	parse_squote(t_mdata *data, t_command *cmd, char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '\'')
			return (i);
		i++;
	}
	cmd->good = -1;
	return (ft_error(data, "Error: simple quote not closed\n", 0), -1);
}

void	parse_cmd(t_mdata *data, t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->line[i])
	{
		if (cmd->line[i] == '"')
			i = parse_dquote(data, cmd, cmd->line, i + 1);
		else if (cmd->line[i] == '\'')
			i = parse_squote(data, cmd, cmd->line, i + 1);
		// else if (cmd->line[i] == '$')
		// 	i = handle_dollar(data, cmd);
		if (i == -1)
			return ;
		i++;
	}
}
