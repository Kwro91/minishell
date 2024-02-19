/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:36:45 by besalort          #+#    #+#             */
/*   Updated: 2024/02/19 20:48:47 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_empty_quotes(t_mdata *data, t_command *cmd, int i)
{
	char	*new;

	new = NULL;
	if (cmd->line[i] == cmd->line[i + 1])
	{
		if (cmd->line[i + 2])
		{
			new = ft_strdup(&cmd->line[i + 2]);
			if (!cmd->line)
				return (ft_error(data, "Error: remove quote1\n", 0), 1);
		}
		else
		{
			new = ft_strdup("");
			if (!cmd->line)
				return (ft_error(data, "Error: remove quote1\n", 0), 1);
		}
		free(cmd->line);
		cmd->line = new;
		return (1);
	}
	return (0);
}

void	get_removed(t_mdata *data, t_command *cmd, int i)
{
	char	*new;
	char	*first;
	char	*second;

	if (!cmd->line)
		return (ft_error(data, "Error: remove quote1\n", 0));
	first = "";
	second = "";
	if (i != 0 && cmd->line[i - 1])
		first = ft_strndup(data, cmd->line, i);
	if (!first)
		return (ft_error(data, "Error: remove quote2\n", 0));
	if (cmd->line[i + 1])
		second = ft_strdup(&cmd->line[i + 1]);
	if (!second)
		return (ft_error(data, "Error: remove quote3\n", 0));
	new = ft_strjoin(first, second);
	if (!new)
		return (ft_error(data, "Error: remove quote4\n", 0));
	if (first && ft_strncmp(first, "", 1) != 0)
		free(first);
	if (second && ft_strncmp(second, "", 1) != 0)
		free(second);
	free(cmd->line);
	cmd->line = new;
}

int	remove_dquote(t_mdata *data, t_command *cmd, int i)
{
	if (check_empty_quotes(data, cmd, i) == 1)
		return (i);
	get_removed(data, cmd, i);
	while (cmd->line[i])
	{
		if (cmd->line[i] == '"')
			return (get_removed(data, cmd, i), i);
		i++;
	}
	return (i);
}

int	remove_squote(t_mdata *data, t_command *cmd, int i)
{
	if (check_empty_quotes(data, cmd, i) == 1)
		return (i);
	get_removed(data, cmd, i);
	while (cmd->line[i])
	{
		if (cmd->line[i] == '\'')
			return (get_removed(data, cmd, i), i);
		i++;
	}
	return (i);
}

void	remove_quotes(t_mdata *data, t_command *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmd->line);
	while (i < len && cmd->line[i])
	{
		if (cmd->line[i] && cmd->line[i] == '"')
			i = remove_dquote(data, cmd, i);
		else if (cmd->line[i] && cmd->line[i] == '\'')
			i = remove_squote(data, cmd, i);
		i++;
		len = ft_strlen(cmd->line);
	}
}