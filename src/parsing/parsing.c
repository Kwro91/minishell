/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:30:01 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 15:26:27 by afontain         ###   ########.fr       */
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
	return (ft_error(data, "Error: double quote not closed\n", 0), -2);
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
	return (ft_error(data, "Error: simple quote not closed\n", 0), -2);
}

void	remove_all_quotes(t_mdata *data, t_command *cmd)
{
	char	**tab;

	tab = cmd->cmd;
	if (!cmd)
		return ;
	while (*tab)
	{
		remove_quotes(data, tab);
		tab++;
	}
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
			i = parse_dquote(data, cmd, i + 1);
		else if (cmd->line[i] == '\'')
			i = parse_squote(data, cmd, i + 1);
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
	remove_all_quotes(data, cmd);
}
