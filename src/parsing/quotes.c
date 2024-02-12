/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:40:00 by afontain          #+#    #+#             */
/*   Updated: 2024/02/12 15:31:03 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] == '\0')
				return (1);
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
			if (str[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	nb_quotes(char *cmd_total)
{
	int	count;
	int i;

	i = 0;
	count = 0;
	while (cmd_total[i])
	{
		if (cmd_total[i] == '"')
		{
			i++;
			while (cmd_total[i] && cmd_total[i] != '"')
				i++;
			i++;
			count += 2;
		}
		else if (cmd_total[i] == 39)
		{
			i++;
			while (cmd_total[i] && cmd_total[i] != 39)
				i++;
			i++;
			count += 2;
		}
		else if (cmd_total[i])
			i++;
	}
	return (count);
}

void	remove_double(char *cmd_total, char *new_cmd, int i, int j)
{
	i++;
	while (cmd_total[i] != '"' && cmd_total[i])
	{
		new_cmd[j] = cmd_total[i];
		i++;
		j++;
	}
	i++;
}

void	remove_single(char *cmd_total, char *new_cmd, int i, int j)
{
	i++;
	while (cmd_total[i] != 39 && cmd_total[i])
	{
		new_cmd[j] = cmd_total[i];
		i++;
		j++;
	}
	i++;
}

char	*remove_quotes(char *cmd_total)
{
	int		i;
	int		j;
	char	*new_cmd;

	i = 0;
	j = 0;
	if (!cmd_total)
		return (NULL);
	new_cmd = malloc(sizeof(char) * ft_strlen(cmd_total) - nb_quotes(cmd_total) + 1);
	if (!new_cmd)
		return (NULL);
	while (cmd_total[i++])
	{
		if (cmd_total[i] == '"')
			remove_double(cmd_total, new_cmd, i, j);
		else if (cmd_total[i] == 39)
			remove_single(cmd_total, new_cmd, i, j);
		else
			new_cmd[j++] = cmd_total[i];
	}
	new_cmd[j] = '\0';
	// free (cmd_total);
	return (new_cmd);
}
