/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:01:29 by afontain          #+#    #+#             */
/*   Updated: 2024/02/23 17:41:44 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_unset(char **cmd_total, t_mdata *data)
{
	char	*name0;
	char	*namen;

	name0 = "unset\0";
	namen = "unset\n\0";
	if (ft_strncmp(name0, cmd_total[0], 6) == 0
		|| ft_strncmp(namen, cmd_total[0], 7) == 0)
	{
		ft_unset(cmd_total, data);
		return (1);
	}
	return (-1);
}

int	is_cd(char **cmd_total, t_mdata *data)
{
	char	*name0;
	char	*namen;

	name0 = "cd\0";
	namen = "cd\n\0";
	if (ft_strncmp(name0, cmd_total[0], 2) == 0
		|| ft_strncmp(namen, cmd_total[0], 3) == 0)
	{
		cd_cmd(data, cmd_total[1]);
		return (1);
	}
	return (-1);
}

int	verif_cmd(t_mdata *data, t_command *cmd)
{
	if (ft_strncmp(cmd->line, "", 1) == 0)
		return (0);
	redir(data, cmd);
	parse_cmd(data, cmd);
	if (cmd->good < 0)
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
