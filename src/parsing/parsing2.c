/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:03:32 by afontain          #+#    #+#             */
/*   Updated: 2024/03/24 18:13:25 by afontain         ###   ########.fr       */
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

int	*create_tab(t_mdata *data)
{
	int	*tab;
	int	i;

	i = 0;
	tab = malloc(sizeof(int) * 4096);
	if (!tab)
		ft_error(data, "Error: malloc\n", -1);
	while (i < 4096)
	{
		tab[i] = -1;
		i++;
	}
	return (tab);
}

void	add_tab(int *tab, int value)
{
	int	i;

	i = 0;
	while (i < 4096 && tab[i] != -1)
		i++;
	tab[i] = value;
}

void	update_tab(int	*tab, int j)
{
	int	i;

	i = 0;
	while (i < 4096 && tab[i])
	{
		if (i >= j)
			tab[i] -= 1;
		i++;
	}
}

int	parse_dquote(t_mdata *data, t_command *cmd, int i, int *tab)
{
	int	len;

	add_tab(tab, i - 1);
	len = ft_strlen(cmd->line);
	while (i < len && cmd->line)
	{
		if (cmd->line[i] == '"')
			return (add_tab(tab, i), i);
		else if (cmd->line[i] == '$')
			i = handle_dollar(data, cmd, i);
		i++;
		len = ft_strlen(cmd->line);
	}
	cmd->good = -1;
	return (ft_error(data, "Error: double quote not closed\n", 2), -2);
}
