/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by besalort          #+#    #+#             */
/*   Updated: 2023/11/30 14:27:10 by afontain         ###   ########.fr       */
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

int	verif_cmd(t_mdata *data, char **cmd_total, char **env)
{
	(void)env;
	if (is_echo(cmd_total) == 1)
		return (1);
    else if (is_pwd(cmd_total, data) == 1)
        return (1);
	else if (is_exit(cmd_total, data) == 1)
		return (1);
	else if (is_env(cmd_total, data) == 1)
		return (1);
    else if (is_unset(cmd_total, data) == 1)
	    return (1);
    return (-1);
}

char	*get_readline(t_mdata *data, char *str)
{
	str = readline("Minishell>");
	if (!str)
	{
		rl_clear_history();
		write(STDERR_FILENO, "exit\n", 5);
		exit_mini(data);
	}
	return (str);
}

void    prompt(int ac, char **av, char **env)
{
	(void)ac;
    (void)av;
    t_mdata	data;
    char	*cmd;
    char	**cmdtotal;

    data.paths = ft_path_mini(env);
	env_setup(&data, env);
    setup_pwd(&data, env, 1);
    while(1)
    {
		cmd = get_readline(&data, "Minishell>");
		if (*cmd)
		{
			add_history(cmd);
			cmdtotal= ft_split(cmd, ' ');
		}
		if (*cmd && verif_cmd(&data, cmdtotal, env) == 0)
		{
			if (ft_access_mini(&data, cmd) != NULL)
				launch_cmd(&data, cmd, cmdtotal, env);
			cmd = NULL;
		}
		if (*cmd)
			free (cmd);
    }
}