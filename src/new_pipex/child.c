/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:40:14 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 15:45:16 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_first_child(t_mdata *data, t_command *cmd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (perror("Error fork\n"), exit_mini(data), (void) NULL);
	if (pid == 0)
	{
		close(data->pipes[0]);
		if (cmd->good == 0)
		{
			if (!cmd->out)
				if (dup2(data->pipes[1], 1) < 0)
					return (ft_error(data, "Error: dup2\n", -1));
			launch_cmd(data, cmd);
		}
		ft_free_lines(cmd->cmd);
		exit_mini(data);
	}
}

void	ft_mid_childs(t_mdata *data, t_command *cmd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (perror("Error fork\n"), exit_mini(data), (void) NULL);
	if (pid == 0)
	{
		if (cmd->good == -1)
			return ;
		if (!cmd->in)
			if (dup2(data->pipe_save, 0) < 0)
				return (ft_error(data, "Error: dup2\n", -1));
		close(data->pipe_save);
		if (!cmd->out)
			if (dup2(data->pipes[1], 1) < 0)
				return (ft_error(data, "Error: dup2\n", -1));
		close(data->pipes[0]);
		close(data->pipes[1]);
		launch_cmd(data, cmd);
		ft_free_lines(cmd->cmd);
		exit_mini(data);
	}
}

void	ft_last_child(t_mdata *data, t_command *cmd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (perror("Error fork\n"), exit_mini(data), (void) NULL);
	if (pid == 0)
	{
		if (cmd->good == 0)
		{
			if (!cmd->in)
				if (dup2(data->pipe_save, 0) < 0)
					return (ft_error(data, "Error: dup2\n", -1));
			close(data->pipes[1]);
			close(data->pipes[0]);
			launch_cmd(data, cmd);
		}
		ft_free_lines(cmd->cmd);
		exit_mini(data);
	}
}
