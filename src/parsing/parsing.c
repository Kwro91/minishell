/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:30:01 by besalort          #+#    #+#             */
/*   Updated: 2024/02/23 16:09:11 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return (ft_error(data, "Error: double quote not closed\n", 2), -2);
}

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
	return (ft_error(data, "Error: simple quote not closed\n", 2), -2);
}

void	remove_all_quotes(t_mdata *data, t_command *cmd)
{
	char	**tab;

	tab = cmd->cmd;
	if (!cmd || !*tab)
		return ;
	while (*tab)
	{
		remove_quotes(data, tab);
		tab++;
	}
}

void	parse_norm(t_mdata *data, t_command *cmd)
{
	char	*cmp;

	ft_free_lines(cmd->cmd);
	if (!cmd->line)
	{
		cmd->good = -1;
		return ;
	}
	cmp = " \t";
	cmd->cmd = split_cmd(data, cmd->line, cmp);
	remove_all_quotes(data, cmd);
}

void	parse_cmd(t_mdata *data, t_command *cmd)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(cmd->line);
	while (i >= 0 && cmd->line && i < len)
	{
		if (cmd->line[i] == '"')
			i = parse_dquote(data, cmd, i + 1);
		else if (cmd->line[i] == '\'')
			i = parse_squote(data, cmd, i + 1);
		else if (cmd->line[i] == '$')
			i = handle_dollar(data, cmd, i);
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
