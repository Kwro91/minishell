/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:26:03 by besalort          #+#    #+#             */
/*   Updated: 2024/02/22 15:40:14 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_echo(char **cmd_total)
{
	char	*name0;
	char	*namen;

	name0 = "echo\0";
	namen = "echo\n\0";
	if (ft_strncmp(name0, cmd_total[0], 5) == 0
		|| ft_strncmp(namen, cmd_total[0], 6) == 0)
	{
		ft_echo(&cmd_total[1]);
		return (1);
	}
	return (-1);
}

int	is_pwd(char **cmd_total, t_mdata *data)
{
	char	*name0;
	char	*namen;

	name0 = "pwd\0";
	namen = "pwd\n\0";
	if (ft_strncmp(name0, cmd_total[0], 4) == 0
		|| ft_strncmp(namen, cmd_total[0], 5) == 0)
	{
		pwd(data);
		return (1);
	}
	return (-1);
}

int	is_exit(char **cmd_total, t_mdata *data)
{
	char	*name0;
	char	*namen;

	name0 = "exit\0";
	namen = "exit\n\0";
	if (ft_strncmp(name0, cmd_total[0], 5) == 0
		|| ft_strncmp(namen, cmd_total[0], 6) == 0)
	{
		exit_mini(data, cmd_total);
		return (1);
	}
	return (-1);
}

int	is_env(char **cmd_total, t_mdata *data)
{
	char	*name0;
	char	*namen;

	name0 = "env\0";
	namen = "env\n\0";
	if (ft_strncmp(name0, cmd_total[0], 4) == 0
		|| ft_strncmp(namen, cmd_total[0], 5) == 0)
	{
		env_cmd(data);
		return (1);
	}
	return (-1);
}

int	is_export(char **cmd_total, t_mdata *data)
{
	char	*name0;
	char	*namen;

	name0 = "export\0";
	namen = "export\n\0";
	if (ft_strncmp(name0, cmd_total[0], 7) == 0
		|| ft_strncmp(namen, cmd_total[0], 8) == 0)
	{
		if (cmd_total[1] != NULL)
			export_cmd(data, cmd_total);
		else
			export_cmd(data, NULL);
		return (1);
	}
	return (-1);
}
