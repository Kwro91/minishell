/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:49:05 by afontain          #+#    #+#             */
/*   Updated: 2024/03/22 14:57:14 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_squote(t_mdata *data, t_command *cmd, int i, int *tab)
{
	int	len;

	add_tab(tab, i - 1);
	len = ft_strlen(cmd->line);
	while (i < len && cmd->line)
	{
		if (cmd->line[i] == '\'')
			return (add_tab(tab, i), i);
		i++;
		len = ft_strlen(cmd->line);
	}
	cmd->good = -1;
	return (ft_error(data, "Error: simple quote not closed\n", 2), -2);
}

void	remove_char2(char *one, char *two, t_mdata *data, t_command *cmd)
{
	if (one && !two)
	{
		ft_free_me(cmd->line);
		cmd->line = ft_strdup(one);
		ft_free_me(one);
		if (!cmd->line)
			return (ft_error(data, "Error: strdup\n", -1));
	}
	else if (!one && two)
	{
		ft_free_me(cmd->line);
		cmd->line = ft_strdup(two);
		ft_free_me(two);
		if (!cmd->line)
			return (ft_error(data, "Error: strdup\n", -1));
	}
}

void	remove_char(t_mdata *data, t_command *cmd, int i)
{
	char	*one;
	char	*two;

	one = NULL;
	two = NULL;
	one = ft_strndup(data, cmd->line, i);
	if (cmd->line[i + 1])
	{
		two = ft_strdup(&cmd->line[i + 1]);
		if (!two)
			return (ft_error(data, "Error: strdup\n", -1));
	}
	if (one && two)
	{
		ft_free_me(cmd->line);
		cmd->line = ft_strjoin(one, two);
		if (!cmd->line)
			return (ft_error(data, "Error: strjoin\n", -1));
		ft_free_me(one);
		ft_free_me(two);
		return ;
	}
	remove_char2(one, two, data, cmd);
}

void	remove_all_quotes(t_mdata *data, t_command *cmd, int *tab)
{
	int	i;

	i = 0;
	while (i < 4096 && tab[i] >= 0)
	{
		remove_char(data, cmd, tab[i]);
		update_tab(tab, i);
		i++;
	}
	i = 0;
	while (i < 4096 && tab[i] > -1)
		i++;
}
