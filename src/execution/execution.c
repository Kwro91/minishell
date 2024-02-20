/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:59:33 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 17:14:17 by afontain         ###   ########.fr       */
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
	ft_error(data, join, 0);
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
	if (cmd->cmd[0] && access(cmd->cmd[0], X_OK) == 0)
	{
		tmp = ft_strdup(cmd->cmd[0]);
		if (!tmp)
			ft_error(data, "Error: strdup\n", 1);
		return (tmp);
	}
	while (cmd->cmd[0] && data->paths && data->paths[i++])
	{
		tmp = ft_strjoin(data->paths[i], "/");
		join = ft_strjoin(tmp, cmd->cmd[0]);
		if (join && access(join, X_OK) == 0)
			return (ft_free_me(tmp), join);
		ft_free_me(join);
		ft_free_me(tmp);
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
		return (ft_error(data, "Error: fork\n", 0));
	if (pid == 0)
	{
		close_all_files(data, cmd);
		execve(path, cmd->cmd, data->env);
		end_loop(data);
		ft_free_me(path);
		exit_mini(data);
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
	char	*tmp;

	if (verif_cmd(data, cmd) == 0)
	{
		close_all_files(data, cmd);
		tmp = ft_access_mini(data, cmd);
		if (tmp)
			execve(tmp, cmd->cmd, data->env);
		ft_free_me(tmp);
	}
	exit_mini(data);
}

void	launch_cmd(t_mdata *data, t_command *cmd)
{
	if (!cmd || cmd->good == -1)
		return ;
	printf("Bonsoir oui je me lance\n");
	if (data->nb_cmd == 1)
		if (verif_cmd(data, cmd) == 0)
			solo_cmd(data, cmd, ft_access_mini(data, cmd));
	if (data->nb_cmd > 1)
		pipe_cmd(data, cmd);
}
