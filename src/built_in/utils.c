/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:15:35 by besalort          #+#    #+#             */
/*   Updated: 2024/02/14 18:38:44 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_cmd(t_mdata *data, t_command *cmd)
{
	if (ft_strncmp(cmd->line, "", 1) == 0)
		return (0);
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
