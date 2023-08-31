/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by besalort          #+#    #+#             */
/*   Updated: 2023/08/31 17:19:56 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	tmp = ft_strjoin(": command not found: ", cmd);
	join = ft_strjoin(tmp, "\n");
	ft_printf("%s\n", join);
	return (free(join), free(tmp), cmd);
}

void	launch_cmd(t_mdata *data, char *cmd, char **cmdtotal, char **env)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		printf("%s\n", cmd);
		execve(ft_access_mini(data, cmd), cmdtotal, env);
		exit(0);
	}
}

void    prompt(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_mdata	data;
    char	*cmd;
    char	**cmdtotal;

    data.paths = ft_path_mini(env);
    (void)data;
    int i = 0;
    
    while (data.paths[i])
    {
        ft_printf("%s\n", data.paths[i]);
        i++;
    }
    while(1)
    {
        ft_printf("type a command>\n");
        cmd = get_next_line(0);
		cmdtotal= ft_split(cmd, 32);
		if (ft_access_mini(&data, cmd) != NULL)
			launch_cmd(&data, cmd, cmdtotal, env);
    }
}