/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:40:00 by afontain          #+#    #+#             */
/*   Updated: 2024/02/16 17:13:10 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// int	check_quotes(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (0);
// 	while (str[i])
// 	{
// 		if (str[i] == '"')
// 		{
// 			i++;
// 			while (str[i] && str[i] != '"')
// 				i++;
// 			if (str[i] == '\0')
// 				return (1);
// 		}
// 		if (str[i] == 39)
// 		{
// 			i++;
// 			while (str[i] && str[i] != 39)
// 				i++;
// 			if (str[i] == '\0')
// 				return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	nb_quotes(char *cmd_total)
// {
// 	int	count;
// 	int i;

// 	i = 0;
// 	count = 0;
// 	while (cmd_total[i])
// 	{
// 		if (cmd_total[i] == '"')
// 		{
// 			i++;
// 			while (cmd_total[i] && cmd_total[i] != '"')
// 				i++;
// 			i++;
// 			count += 2;
// 		}
// 		else if (cmd_total[i] == 39)
// 		{
// 			i++;
// 			while (cmd_total[i] && cmd_total[i] != 39)
// 				i++;
// 			i++;
// 			count += 2;
// 		}
// 		else if (cmd_total[i])
// 			i++;
// 	}
// 	return (count);
// }

// void	remove_double(char *cmd_total, char *new_cmd, int i, int j)
// {
// 	i++;
// 	while (cmd_total[i] != '"' && cmd_total[i])
// 	{
// 		new_cmd[j] = cmd_total[i];
// 		i++;
// 		j++;
// 	}
// 	i++;
// }

// void	remove_single(char *cmd_total, char *new_cmd, int i, int j)
// {
// 	i++;
// 	while (cmd_total[i] != 39 && cmd_total[i])
// 	{
// 		new_cmd[j] = cmd_total[i];
// 		i++;
// 		j++;
// 	}
// 	i++;
// }

// char	*remove_quotes(t_command *cmd)
// {
// 	int		i;
// 	int		j;
// 	char	*new_cmd;

// 	i = 0;
// 	j = 0;
// 	if (!cmd->line)
// 		return (NULL);
// 	// printf("On obtient: %i\n", ((int)ft_strlen(cmd->line) - nb_quotes(cmd->line) + 1));
// 	new_cmd = malloc(sizeof(char) * (ft_strlen(cmd->line) - nb_quotes(cmd->line) + 1));
// 	if (!new_cmd)
// 		return (NULL);
// 	if (cmd->line[i] == '\'' || cmd->line[i] == '"')
// 		i++;
// 	while (cmd->line[i])
// 	{
// 		if (cmd->line[i] == '"')
// 			remove_double(cmd->line, new_cmd, i, j);
// 		else if (cmd->line[i] == 39)
// 			remove_single(cmd->line, new_cmd, i, j);
// 		else
// 			new_cmd[j++] = cmd->line[i];
// 		i++;
// 	}
// 	new_cmd[j] = '\0';
// 	// printf("%s\n", new_cmd);
// 	free (cmd->line);
// 	cmd->line = new_cmd;
// 	return (new_cmd);
// }
