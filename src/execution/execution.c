/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:59:33 by besalort          #+#    #+#             */
/*   Updated: 2024/01/10 16:02:03 by besalort         ###   ########.fr       */
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
		// ft_printf("%s : %i\n", join, access(join, X_OK));
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
	// return (cmd);
}

void	launch_cmd(t_mdata *data, char **cmdtotal, char **env)
{
	int pid;
	int	value;
	int	status;

	pid = fork();
	// int i = 0;
	// while (cmdtotal[i])
	// {
	// 	printf("%s\n", cmdtotal[i++]);
	// }
	if (pid == 0)
	{
		// printf("je me lance %s\n", cmd);
		value = execve(ft_access_mini(data, cmdtotal[0]), cmdtotal, env);
		//ICI FAUDRA TOUT FREE
		exit(value);
	}
	else
		waitpid(-1, &status, 0);
}