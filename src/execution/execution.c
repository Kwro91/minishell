/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:59:33 by besalort          #+#    #+#             */
/*   Updated: 2024/03/24 18:40:53 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	solo_cmd2(t_mdata *data, t_command *cmd, char *path)
{
	close_all_files(data, cmd);
	handle_signals_exec();
	close_two(data, data->stdin_back, data->stdout_back);
	g_retval = execve(path, cmd->cmd, data->env);
	ft_free_me(path);
	exit_mini(data, NULL);
}

void	solo_cmd(t_mdata *data, t_command *cmd, char *path)
{
	int	pid;
	int	status;

	if (!path)
		return (ft_free_me(path));
	pid = fork();
	if (pid == -1)
		return (ft_error(data, "Error: fork\n", -1));
	if (pid == 0)
		solo_cmd2(data, cmd, path);
	else
	{
		ft_free_me(path);
		signal(SIGINT, SIG_IGN);
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			g_retval = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			g_retval = 128 + WTERMSIG(status);
			error_signal();
		}
		close_all_files(data, cmd);
	}
}

void	pipe_cmd(t_mdata *data, t_command *cmd)
{
	DIR		*dir;
	char	*tmp;

	do_redir(data, cmd);
	if (verif_cmd(data, cmd) == 0)
	{
		close_all_files(data, cmd);
		close_two(data, data->stdin_back, data->stdout_back);
		tmp = ft_access_mini(data, cmd);
		dir = opendir(tmp);
		loop_directory(data, cmd, tmp, dir);
		if (tmp && cmd->good != -1)
			g_retval = execve(tmp, cmd->cmd, data->env);
		ft_free_me(tmp);
	}
	exit_mini(data, NULL);
}

void	launch_cmd(t_mdata *data, t_command *cmd)
{
	DIR		*dir;
	char	*path;

	printf("blokc :%i\n", data->block);
	ft_error(data, "block\n", 0);
	if (!cmd || cmd->good == -1 || data->block == -1)
		return ;
	handle_signals();
	if (data->nb_cmd == 1)
	{
		parse_cmd(data, cmd);
		dir = opendir(cmd->line);
		do_redir(data, cmd);
		if (cmd->good != -1 && verif_cmd(data, cmd) == 0)
		{
			path = ft_access_mini(data, cmd);
			loop_directory(data, cmd, path, dir);
			solo_cmd(data, cmd, path);
		}
	}
	if (data->nb_cmd > 1)
		pipe_cmd(data, cmd);
	handle_signals();
}
