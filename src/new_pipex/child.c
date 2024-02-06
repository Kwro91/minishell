/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:40:14 by besalort          #+#    #+#             */
/*   Updated: 2024/02/06 12:42:12 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	ft_first_child(t_mdata *data, t_command *cmd)
{
	int	pid;
	
	pid = fork();
	if (pid == -1)
		return (perror("Error fork\n"), ft_exit(data), NULL);
	if (pid == 0)
	{
		redir(data, cmd);
		// dup_me(data, cmd->in, cmd->out);
		if (cmd->good == -1)
			return ;
		if (!cmd->out)
			if (dup2(data->pipes[1], 1) < 0)
				return (ft_error(data, "Error: dup2\n", 1));
		exit(0);
	}
}

void	ft_mid_childs(t_mdata *data, t_command *cmd)
{
	int	pid;
	
	pid = fork();
	if (pid == -1)
		return (perror("Error fork\n"), ft_exit(data), NULL);
	if (pid == 0)
	{
		redir(data, cmd);
		// dup_me(data, cmd->in, cmd->out);
		if (cmd->good == -1)
			return ;
		if (!cmd->in)
			if (dup2(data->pipes[0], 0) < 0)
				return (ft_error(data, "Error: dup2\n", 1));
		if (!cmd->out)
			if (dup2(data->pipes[1], 1) < 0)
				return (ft_error(data, "Error: dup2\n", 1));
		exit(0);
	}
}

void	ft_last_child(t_mdata *data, t_command *cmd)
{
	int	pid;
	
	pid = fork();
	if (pid == -1)
		return (perror("Error fork\n"), ft_exit(data), NULL);
	if (pid == 0)
	{
		redir(data, cmd);
		// dup_me(data, cmd->in, cmd->out);
		if (cmd->good == -1)
			return ;
		if (!cmd->in)
			if (dup2(data->pipes[0], 0) < 0)
				return (ft_error(data, "Error: dup2\n", 1));
		exit(0);
	}
}