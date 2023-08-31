/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:32:19 by besalort          #+#    #+#             */
/*   Updated: 2023/07/06 15:39:34 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_first(t_pipex *data, t_lst *tmp)
{
	if (pipe(data->pipes) < 0)
		return (perror("Error pipe\n"), ft_free(data));
	if (data->fd_in >= 0)
	{
		ft_first_process(data, tmp->command, data->pipes);
	}
	close(data->pipes[1]);
	close (data->fd_in);
	data->fd_in = data->pipes[0];
}

t_lst	*run_other(t_pipex *data, t_lst *tmp)
{
	while (tmp->next)
	{
		if (pipe(data->pipes) < 0)
			return (perror("Error pipe\n"), ft_free(data), tmp);
		ft_processes(data, tmp->command, data->pipes);
		close(data->pipes[1]);
		close(data->fd_in);
		data->fd_in = data->pipes[0];
		tmp = tmp->next;
	}
	return (tmp);
}

void	run_last(t_pipex *data, t_lst *tmp)
{
	ft_last_process(data, tmp->command, data->pipes);
	close_give_fd(data->pipes[0], data->pipes[1]);
	close(data->fd_in);
}

void	wait_childs(t_pipex *data)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (i < data->cmds)
	{
		waitpid(-1, &status, 0);
		if (i == 0)
		{
			close(data->pipes[1]);
			close(data->pipes[0]);
		}
		i++;
	}
	if (WIFEXITED (status))
		data->status = WEXITSTATUS(status);
	if (WIFSIGNALED (status))
		data->status = WTERMSIG(status);
}

void	run_processes(t_pipex *data)
{
	t_lst	*tmp;

	data->fd_in = data->file1.fd;
	tmp = data->lst;
	run_first(data, tmp);
	tmp = tmp->next;
	tmp = run_other(data, tmp);
	run_last(data, tmp);
	wait_childs(data);
}
