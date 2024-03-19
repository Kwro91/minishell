/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:30:01 by besalort          #+#    #+#             */
/*   Updated: 2024/03/19 19:11:01 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	else if (one && !two)
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

void	remove_all_quotes(t_mdata *data, t_command *cmd, int *tab)
{
	// char	**tab;

	// tab = cmd->cmd;
	// if (!cmd || !*tab)
	// while (*tab)
	// {
		// remove_quotes(data, tab);
		// tab++;
	// }
	// remove_quotes(data, &cmd->line);
	int	i;

	i = 0;
	while(i < 4096 && tab[i] >= 0)
	{
		// printf("line:%s:\n", cmd->line);
		// printf("char a retirer :cmd->line[%i]=[%c]:\n", tab[i], cmd->line[tab[i]]);
		remove_char(data, cmd, tab[i]);
		update_tab(tab, i);
		i++;
	}
	i = 0;
	printf("line:%s:\n", cmd->line);
	while (i < 4096 && tab[i] > -1)
	{
		printf("On splitera a :cmd->line[%i]=%c:\n", tab[i] + 1, cmd->line[tab[i] + 1]);
		i++;
	}
}

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

void	parse_cmd(t_mdata *data, t_command *cmd)
{
	int		i;
	int		*tab;
	
	int		len;

	i = 0;
	tab = create_tab(data);
	// printf("line:%s:\n", cmd->line);
	if (!cmd->line)
	{
		cmd->good = -1;
		return ;
	}
	len = ft_strlen(cmd->line);
	while (i >= 0 && cmd->line && i < len)
	{
		if (cmd->line[i] == '"')
			i = parse_dquote(data, cmd, i + 1, tab);
		else if (cmd->line[i] == '\'')
			i = parse_squote(data, cmd, i + 1, tab);
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
	parse_norm(data, cmd, tab);
	free(tab);
}
