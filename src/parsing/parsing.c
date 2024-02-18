/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:30:01 by besalort          #+#    #+#             */
/*   Updated: 2024/02/18 20:28:21 by besalort         ###   ########.fr       */
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
			i = handle_dollar(data, cmd, i);
		i++;
	}
	cmd->good = -1;
	return (ft_error(data, "Error: double quote not closed\n", 0), -2);
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
	return (ft_error(data, "Error: simple quote not closed\n", 0), -2);
}

void	parse_cmd(t_mdata *data, t_command *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmd->line);
	while (i >= 0 && cmd->line && i < len)
	{
		
		if (cmd->line[i] == '"')
			i = parse_dquote(data, cmd, cmd->line, i + 1);
		else if (cmd->line[i] == '\'')
			i = parse_squote(data, cmd, cmd->line, i + 1);
		else if (cmd->line[i] == '$')
			i = handle_dollar(data, cmd, i);
		if (i == -1)
		{
			cmd->good = -1;
			return ;
		}
		i++;
		len = ft_strlen(cmd->line);
	}
	remove_quotes(data, cmd);
}
