/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:30:01 by besalort          #+#    #+#             */
/*   Updated: 2024/03/22 14:48:55 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_norm(t_mdata *data, t_command *cmd, int *tab)
{
	char	*cmp;

	ft_free_lines(cmd->cmd);
	if (!cmd->line)
	{
		cmd->good = -1;
		return ;
	}
	cmp = " \t";
	remove_all_quotes(data, cmd, tab);
	cmd->cmd = split_cmd(data, cmd->line, cmp);
}

int	parse_cmd2(int i, t_command *cmd, t_mdata *data, int *tab)
{
	if (cmd->line[i] == '"')
		i = parse_dquote(data, cmd, i + 1, tab);
	else if (cmd->line[i] == '\'')
		i = parse_squote(data, cmd, i + 1, tab);
	else if (cmd->line[i] == '$')
		i = handle_dollar(data, cmd, i);
	return (i);
}

void	parse_cmd(t_mdata *data, t_command *cmd)
{
	int		i;
	int		*tab;
	int		len;

	i = 0;
	tab = create_tab(data);
	if (!cmd->line)
	{
		cmd->good = -1;
		return ;
	}
	len = ft_strlen(cmd->line);
	while (i >= 0 && cmd->line && i < len)
	{
		i = parse_cmd2(i, cmd, data, tab);
		if (i < 0)
		{
			cmd->good = -1;
			return ;
		}
		i++;
		len = ft_strlen(cmd->line);
	}
	parse_norm(data, cmd, tab);
	free(tab);
}
