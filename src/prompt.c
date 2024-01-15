/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by besalort          #+#    #+#             */
/*   Updated: 2024/01/15 13:35:07 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (is_export(cmd_total, data) == 1)
		return (1);
	else if (is_unset(cmd_total, data) == 1)
		return (1);
	else if (is_cd(cmd_total, data) == 1)
		return (1);
	return (0);
}

char	*get_readline(t_mdata *data, char *str)
{
	str = readline("Minishell> ");
	if (!str)
	{
		rl_clear_history();
		write(STDERR_FILENO, "exit\n", 5);
		exit_mini(data);
	}
	return (str);
}

void	prompt(t_mdata *data, int ac, char **av, char **env)
{
	char	*cmd;
	char	**cmdtotal;

	(void)ac;
	(void)av;
	data->paths = ft_path_mini(env);
	env_setup(data, env);
	setup_pwd(data, env, 1);
	while (1)
	{
		cmd = get_readline(data, "Minishell> ");
		if (*cmd && ft_strncmp(cmd, "/n", 2) != 0)
		{
			add_history(cmd);
			cmdtotal = ft_split(cmd, ' ');
			if (verif_cmd(data, cmdtotal, env) == 0)
			{
				if (cmd != NULL)
					launch_cmd(data, cmdtotal, env);
			}
			free (cmd);
			if (*cmdtotal)
				ft_free_lines(cmdtotal);
		}
	}
}
