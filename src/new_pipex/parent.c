/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:38:09 by besalort          #+#    #+#             */
/*   Updated: 2024/02/12 15:30:21 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rfirst(t_mdata *data, t_command *cmd)
{
	if (pipe(data->pipes) < 0)
		return (ft_error(data, "Error: pipe\n", 0),
			exit_mini(data), (void) NULL);
	ft_first_child(data, cmd, ft_access_mini(data, cmd->cmd[0]));
	close(data->pipes[1]);
	data->pipe_save = data->pipes[0];
}

t_command	*rmiddle(t_mdata *data, t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp->next)
	{
		if (pipe (data->pipes) < 0)
			ft_error(data, "Error: pipe\n", 1);
		ft_mid_childs(data, tmp, ft_access_mini(data, cmd->cmd[0]));
		close(data->pipes[1]);
		close(data->pipe_save);
		data->pipe_save = data->pipes[0];
		tmp = tmp->next;
	}
	return (tmp);
}

void	rlast(t_mdata *data, t_command *cmd)
{
	ft_last_child(data, cmd, ft_access_mini(data, cmd->cmd[0]));
	close_two(data, data->pipes[0], data->pipes[1]);
	close(data->pipe_save);
}

void	mwait_childs(t_mdata *data)
{
	int			status;
	int			count;
	t_command	*tmp;

	status = 0;
	count = 0;
	tmp = data->cmd;
	while (tmp)
	{
		waitpid(-1, &status, 0);
		if (count == 0)
		{
			close(data->pipes[1]);
			close(data->pipes[0]);
		}
		count++;
		tmp = tmp->next;
	}
}

void	run_all(t_mdata *data)
{
	t_command	*tmp;

	tmp = data->cmd;
	rfirst(data, tmp);
	tmp = tmp->next;
	tmp = rmiddle(data, tmp);
	rlast(data, tmp);
	mwait_childs(data);
}
