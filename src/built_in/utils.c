/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:15:35 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 15:57:25 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_cmd(t_mdata *data, t_command *cmd)
{
	if (ft_strncmp(cmd->line, "", 1) == 0)
		return (0);
	redir(data, cmd);
	parse_cmd(data, cmd);
	if (is_echo(cmd->cmd) == 1)
		return (1);
	else if (is_pwd(cmd->cmd, data) == 1)
		return (1);
	else if (is_exit(cmd->cmd, data) == 1)
		return (1);
	else if (is_env(cmd->cmd, data) == 1)
		return (1);
	else if (is_export(cmd->cmd, data) == 1)
		return (1);
	else if (is_unset(cmd->cmd, data) == 1)
		return (1);
	else if (is_cd(cmd->cmd, data) == 1)
		return (1);
	return (0);
}

int	nb_word(char **text)
{
	int	i;

	i = 0;
	while (text && text[i])
		i++;
	return (i);
}

void	good_print(char	*line)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	if (!line)
		return ;
	while (line[i])
	{
		ft_printf("%c", line[i]);
		if (line[i] == '=' && equal == 0)
		{
			equal = 1;
			ft_printf("\"");
		}
		i++;
	}
	if (equal == 1)
		ft_printf("\"");
}

char	*next_word(t_mdata *data, char *line)
{
	int	i;
	int	count;
	int	apo;

	i = 0;
	apo = 0;
	count = 0;
	while (ft_strlen(line) > 0 && line[i] == ' ')
		i++;
	while ((int)ft_strlen(line) > i && line[i])
	{
		if (line[i] == '"' && apo == 0)
		{
			apo = 1;
			i++;
		}
		if ((line[i] == '"' && apo == 1)
			|| (apo == 0 && ft_isalnum(line[i]) == 0))
			break ;
		i++;
		count++;
	}
	if (count == 0)
		return (NULL);
	return (dup_word(data, &line[i - count], count));
}
