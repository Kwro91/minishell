/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:30:01 by besalort          #+#    #+#             */
/*   Updated: 2024/03/26 16:34:26 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_norm(t_mdata *data, t_command *cmd)
{
	char	*cmp;
	int		i;

	i = 0;
	ft_free_lines(cmd->cmd);
	if (!cmd->line)
	{
		cmd->good = -1;
		return ;
	}
	cmp = " \t";
	cmd->cmd = split_cmd(data, cmd->line, cmp);
	while (cmd->cmd[i])
	{
		remove_quotes(data, &cmd->cmd[i]);
		i++;
	}
}

int	parse_cmd2(int i, t_command *cmd, t_mdata *data)
{
	if (cmd->line[i] == '"')
		i = parse_dquote(data, cmd, i + 1);
	else if (cmd->line[i] == '\'')
		i = parse_squote(data, cmd, i + 1);
	else if (cmd->line[i] == '$')
		i = handle_dollar(data, cmd, i);
	return (i);
}

void	parse_cmd(t_mdata *data, t_command *cmd)
{
	int		i;
	int		len;

	i = 0;
	if (!cmd->line)
	{
		cmd->good = -1;
		return ;
	}
	len = ft_strlen(cmd->line);
	while (i >= 0 && cmd->line && i < len)
	{
		i = parse_cmd2(i, cmd, data);
		if (i < 0)
		{
			cmd->good = -1;
			return ;
		}
		i++;
		len = ft_strlen(cmd->line);
	}
	parse_norm(data, cmd);
}
