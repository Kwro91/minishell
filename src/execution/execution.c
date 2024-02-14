/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:59:33 by besalort          #+#    #+#             */
/*   Updated: 2024/02/14 16:26:21 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_access_mini(t_mdata *data, char *cmd)
{
	char *tmp;
	char *join;

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
	ft_error(data, join, 0);
	ft_free_me(tmp);
	ft_free_me(join);
}

char	*ft_access_mini(t_mdata *data, char *cmd)
{
	char	*join;
	char	*tmp;
	int		i;

	i = 0;
	if (cmd && access(cmd, X_OK) == 0)
		return (cmd);
	while (cmd && data->paths && data->paths[i])
	{
		tmp = ft_strjoin(data->paths[i], "/");
		join = ft_strjoin(tmp, cmd);
		if (join && access(join, X_OK) == 0)
			return (ft_free_me(tmp), join);
		ft_free_me(join);
		ft_free_me(tmp);
		i++;
	}
	error_access_mini(data, cmd);
	return (NULL);
}

void	solo_cmd(t_mdata *data, t_command *cmd, char *path)
{
	int	pid;
	int	value;
	int	status;

	if (!path)
		return (free(path));
	pid = fork();
	if (pid == -1)
		return (ft_error(data, "Error: fork\n", 0));
	if (pid == 0)
	{
		value = redir(data, cmd);
		close_all_files(data, cmd);
		if (value == 0)
			value = execve(path, cmd->cmd, data->env);
		end_loop(data);
		ft_free_me(path);
		exit(value);
	}
	else
	{
		ft_free_me(path);
		waitpid(-1, &status, 0);
		close_all_files(data, cmd);
	}
}

void	pipe_cmd(t_mdata *data, t_command *cmd)
{
	int	value;

	value = 0;
	if (verif_cmd(data, cmd) == 0)
		value = execve(ft_access_mini(data,
					cmd->cmd[0]), cmd->cmd, data->env);
	close_all_files(data, cmd);
	exit(value);
}

void	launch_cmd(t_mdata *data, t_command *cmd)
{
	if (cmd->good == -1)
		return ;
	if (data->nb_cmd == 1)
		if (verif_cmd(data, cmd) == 0)
			solo_cmd(data, cmd, ft_access_mini(data, cmd->cmd[0]));
	if (data->nb_cmd > 1)
		pipe_cmd(data, cmd);
}
