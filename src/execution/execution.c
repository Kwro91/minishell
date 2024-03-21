/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:59:33 by besalort          #+#    #+#             */
/*   Updated: 2024/03/21 17:23:58 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_access_mini(t_mdata *data, char *cmd)
{
	char	*tmp;
	char	*join;

	join = NULL;
	tmp = NULL;
	if (cmd != NULL && ft_strncmp(cmd, "\0", 1) != 0)
	{
		tmp = ft_strjoin("minishell: command not found222: ", cmd);
		join = ft_strjoin(tmp, "\n");
	}
	else
	{
		tmp = ft_strdup("minishell: command not found444: ");
		join = ft_strjoin(tmp, "\n");
	}
	ft_error(data, join, 127);
	ft_free_me(tmp);
	ft_free_me(join);
}

char	*ft_access_mini(t_mdata *data, t_command *cmd)
{
	char	*join;
	char	*tmp;
	int		i;

	i = 0;
	if (!cmd->cmd)
		return (NULL);
	if (ft_strncmp(cmd->cmd[0], "", 1) == 0)
		return (ft_error(data, "minishell: command not found: \n", 127), NULL);
	if (cmd->cmd[0] && access(cmd->cmd[0], X_OK) == 0)
		return (tmp = access_utils(data, cmd));
	while (cmd->cmd[0] && data->paths && data->paths[i])
	{
		tmp = ft_strjoin(data->paths[i], "/");
		join = ft_strjoin(tmp, cmd->cmd[0]);
		if (join && access(join, X_OK) == 0)
			return (ft_free_me(tmp), join);
		ft_free_me(join);
		ft_free_me(tmp);
		i++;
	}
	error_access_mini(data, cmd->cmd[0]);
	return (NULL);
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
	{
		close_all_files(data, cmd);
		handle_signals_exec();
		close_two(data, data->stdin_back, data->stdout_back);
		g_retval = execve(path, cmd->cmd, data->env);
		end_loop(data);
		ft_free_me(path);
		exit_mini(data, NULL);
	}
	else
	{
		ft_free_me(path);
		signal(SIGINT, SIG_IGN);
		waitpid(-1, &status, 0);
		if (WIFEXITED(status)){
			g_retval = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			g_retval = 128 + WTERMSIG(status);
			error_signal();
		}
		close_all_files(data, cmd);
	}
}

void    pipe_cmd(t_mdata *data, t_command *cmd)
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

void    launch_cmd(t_mdata *data, t_command *cmd)
{
    DIR		*dir;
    char	*path;
    
    if (!cmd || cmd->good == -1)
        return ;
    handle_signals();
    if (data->nb_cmd == 1)
    {
		// redir(data, cmd);
		// sub_files(data, cmd);
		parse_cmd(data, cmd);
		// printf("line:%s:\n", cmd->line);
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
