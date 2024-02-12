/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by besalort          #+#    #+#             */
/*   Updated: 2024/02/12 15:22:00 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	loop(t_mdata *data, char *cmd)
{
	t_command	*tmp;

	data->nb_cmd = 0;
	cmd = get_readline(data, "Minishell> ");
	if (*cmd && ft_strncmp(cmd, "\n\0", 2) != 0)
	{
		add_history(cmd);
		data->cmd = NULL;
		if (cmd != NULL && check_before(data, cmd) == 1)
		{
			split_parse(data, cmd);
			tmp = data->cmd;
			while (tmp)
			{
				sub_files(data, tmp);
				tmp = tmp->next;
			}
			if (data->nb_cmd == 1)
				launch_cmd(data, data->cmd);
			else if (data->nb_cmd > 1)
				mpipex(data);
		}
		end_loop(data);
		free (cmd);
	}
}

void	prompt(t_mdata *data, char **env)
{
	char	*cmd;

	cmd = NULL;
	data->paths = ft_path_mini(env);
	env_setup(data, env);
	setup_pwd(data, env, 1);
	while (1)
	{
		if (do_line_exist(data->env, "PWD") == -1)
			add_pwd(data);
		loop(data, cmd);
	}
}
