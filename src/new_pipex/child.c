/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:40:14 by besalort          #+#    #+#             */
/*   Updated: 2024/03/21 17:31:12 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_first_child(t_mdata *data, t_command *cmd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (perror("Error fork\n"), exit_mini(data, NULL), (void) NULL);
	if (pid == 0)
	{
		data->pipes[0] = ft_close_me(data->pipes[0]);
		if (cmd->good == 0)
		{
			if (!cmd->out)
				if (dup2(data->pipes[1], 1) < 0)
					return (ft_error(data, "Error: dup21\n", -1));
			data->pipes[1] = ft_close_me(data->pipes[1]);
			launch_cmd(data, cmd);
		}
		ft_free_lines(cmd->cmd);
		exit_mini(data, NULL);
	}
}

void	ft_mid_childs(t_mdata *data, t_command *cmd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (perror("Error fork\n"), exit_mini(data, NULL), (void) NULL);
	if (pid == 0)
	{
		if (cmd->good == -1)
			return ;
		if (!cmd->in)
			if (dup2(data->pipe_save, 0) < 0)
				return (ft_error(data, "Error: dup22\n", -1));
		data->pipe_save = ft_close_me(data->pipe_save);
		if (!cmd->out)
			if (dup2(data->pipes[1], 1) < 0)
				return (ft_error(data, "Error: dup23\n", -1));
		data->pipes[0] = ft_close_me(data->pipes[0]);
		data->pipes[1] = ft_close_me(data->pipes[1]);
		launch_cmd(data, cmd);
		ft_free_lines(cmd->cmd);
		exit_mini(data, NULL);
	}
}

void	ft_last_child(t_mdata *data, t_command *cmd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (perror("Error fork\n"), exit_mini(data, NULL), (void) NULL);
	if (pid == 0)
	{
		if (cmd->good == 0)
		{
			if (!cmd->in)
				if (dup2(data->pipe_save, 0) < 0)
					return (ft_error(data, "Error: dup24\n", -1));
			// printf("fd pipe0: %d\n", data->pipes[0]);
			// printf("fd pipe1: %d\n", data->pipes[1]);
			data->pipes[0] = ft_close_me(data->pipes[0]);
			data->pipes[1] = ft_close_me(data->pipes[1]);
			launch_cmd(data, cmd);
		}
		ft_free_lines(cmd->cmd);
		exit_mini(data, NULL);
	}
}
