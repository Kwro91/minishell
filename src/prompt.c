/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by besalort          #+#    #+#             */
/*   Updated: 2023/09/06 13:44:21 by besalort         ###   ########.fr       */
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
		// ft_printf("%s : %i\n", join, access(join, X_OK));
		if (access(join, X_OK) == 0)
			return (free(tmp), join);
		free(join);
		free(tmp);
		i++;
	}
	// tmp = ft_strjoin(": command not found: ", cmd);
	// join = ft_strjoin(tmp, "\n");
	// ft_printf("%s\n", join);
	// return (free(join), free(tmp), cmd);
	return (cmd);
}

void	launch_cmd(t_mdata *data, char *cmd, char **cmdtotal, char **env)
{
	int pid;

	pid = fork();
	// int i = 0;
	// while (cmdtotal[i])
	// {
	// 	printf("%s\n", cmdtotal[i++]);
	// }
	if (pid == 0)
	{
		// printf("je me lance %s\n", cmd);
		execve(ft_access_mini(data, cmd), cmdtotal, env);
		exit(0);
	}
}

int	verif_cmd(t_mdata *data, char *cmd, char **cmd_total, char **env)
{
	(void)cmd;
	(void)env;
	if (is_echo(cmd_total) == 1)
		return (1);
    else if (is_pwd(cmd_total, data) == 1)
        return (1);
    else
	    return (0);
    return (0);
}

void    prompt(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_mdata	data;
    char	*cmd;
    char	**cmdtotal;

    data.paths = ft_path_mini(env);
    setup_pwd(&data, env);
    while(1)
    {
        ft_printf("type a command>\n");
        cmd = get_next_line(0);
		cmdtotal= ft_split(cmd, ' ');
		if (verif_cmd(&data, cmd, cmdtotal, env) == 0)
		{
			if (ft_access_mini(&data, cmd) != NULL)
				launch_cmd(&data, cmd, cmdtotal, env);
			cmd = NULL;
		}
    }
}