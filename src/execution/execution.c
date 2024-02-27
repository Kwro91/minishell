/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:59:33 by besalort          #+#    #+#             */
/*   Updated: 2024/02/27 17:19:18 by besalort         ###   ########.fr       */
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
		tmp = ft_strjoin("minishell: command not found: ", cmd);
		join = ft_strjoin(tmp, "\n");
	}
	else
	{
		tmp = ft_strdup("minishell: command not found: ");
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
		signal(SIGQUIT, handle_sigquit);
		close_all_files(data, cmd);
		g_retval = execve(path, cmd->cmd, data->env);
		end_loop(data);
		ft_free_me(path);
		exit_mini(data, NULL);
	}
	else
	{
		ft_free_me(path);
		waitpid(-1, &status, 0);
		g_retval = WEXITSTATUS(status);
		close_all_files(data, cmd);
	}
}

void	pipe_cmd(t_mdata *data, t_command *cmd)
{
	char	*tmp;

	signal(SIGQUIT, handle_sigquit);
	if (verif_cmd(data, cmd) == 0)
	{
		close_all_files(data, cmd);
		tmp = ft_access_mini(data, cmd);
		if (tmp)
			g_retval = execve(tmp, cmd->cmd, data->env);
		ft_free_me(tmp);
	}
	exit_mini(data, NULL);
}

void	launch_cmd(t_mdata *data, t_command *cmd)
{
	if (!cmd || cmd->good == -1)
		return ;
	handle_sigint_exec();
	if (data->nb_cmd == 1)
		if (verif_cmd(data, cmd) == 0)
			solo_cmd(data, cmd, ft_access_mini(data, cmd));
	if (data->nb_cmd > 1)
		pipe_cmd(data, cmd);
	handle_signals();
}
