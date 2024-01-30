/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:59:33 by besalort          #+#    #+#             */
/*   Updated: 2024/01/30 14:49:56 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_access_mini(t_mdata *data, char *cmd)
{
	char	*join;
	char	*tmp;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (data->paths[i])
	{
		tmp = ft_strjoin(data->paths[i], "/");
		join = ft_strjoin(tmp, cmd);
		if (access(join, X_OK) == 0)
			return (free(tmp), join);
		free(join);
		free(tmp);
		i++;
	}
	tmp = ft_strjoin("minishell: command not found: ", cmd);
	join = ft_strjoin(tmp, "\n");
	ft_printf("%s", join);
	return (free(join), free(tmp), cmd);
}

void	launch_cmd(t_mdata *data, t_command *cmd)
{
	int	pid;
	int	value;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		value = redir(data, cmd);
		if (value == 0 && verif_cmd(data, cmd) == 0)
			value = execve(ft_access_mini(data, cmd->cmd[0]), cmd->cmd, data->env);
		//ICI FAUDRA TOUT FREE && PASSER LA VALUE EN GLOBALE POUR LE $?
		close_all_files(data, cmd);
		exit(value);
	}
	else
		waitpid(-1, &status, 0);
}
