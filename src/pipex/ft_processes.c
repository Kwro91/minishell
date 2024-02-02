/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_processes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:00:04 by besalort          #+#    #+#             */
/*   Updated: 2024/01/31 13:03:34 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_first_process(t_pipex *data, char **cmdp,
			int pipes[2], t_mdata *mini)
{
	int		pid;
	int		value;
	(void)mini;
	(void)cmdp;
	value = 0;
	pid = fork();
	if (pid == -1)
		return (perror("Error fork\n"), ft_free(data));
	else if (pid == 0)
	{
		if (dup2(data->fd_in, 0) < 0)
			return (ft_free(data));
		close(data->fd_in);
		if (dup2(pipes[1], 1) < 0)
			return (ft_free(data));
		close_give_fd(pipes[1], pipes[0]);
		// if (verif_cmd(mini, cmdp, mini->env) == 0)
			// value = execve(ft_access_cmd(data, cmdp[0]), cmdp, data->data.env);
		ft_free(data);
		exit(value);
	}
}

void	ft_processes(t_pipex *data, char **cmdp, int pipes[2], t_mdata *mini)
{
	int		pid;
	int		value;
	//DANS LES 3 FCT JAI TOUT CASSE AU MEME ENDROIT AVEC LE COMMENTAIRE ET LES DEUX VOID
	(void)mini;
	(void)cmdp;
	value = 0;
	pid = fork();
	if (pid == -1)
		return (perror("Error fork\n"), ft_free(data));
	else if (pid == 0)
	{
		if (dup2(data->fd_in, 0) < 0 || dup2(pipes[1], 1) < 0)
			return (ft_free(data));
		close(data->fd_in);
		close_give_fd(pipes[1], pipes[0]);
		// if (verif_cmd(mini, cmdp, mini->env) == 0)
			// value = execve(ft_access_cmd(data, cmdp[0]), cmdp, data->data.env);
		ft_free(data);
		exit(value);
	}
}

void	ft_last_process(t_pipex *data, char **cmdp, int pipes[2], t_mdata *mini)
{
	int		pid;
	int		value;
	(void)mini;
	(void)cmdp;
	value = 0;
	pid = fork();
	if (pid == -1)
		return (perror("Error fork\n"), ft_free(data));
	else if (pid == 0)
	{
		if (dup2(data->fd_in, 0) < 0 || dup2(data->file2.fd, 1) < 0)
			return (ft_free(data));
		close(data->fd_in);
		close_give_fd(pipes[1], pipes[0]);
		// if (verif_cmd(mini, cmdp, mini->env) == 0)
			// value = execve(ft_access_cmd(data, cmdp[0]), cmdp, data->data.env);
		ft_free(data);
		exit(value);
	}
}
