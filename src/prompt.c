/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by besalort          #+#    #+#             */
/*   Updated: 2024/03/24 18:44:05 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_readline(t_mdata *data, char *str)
{
	str = readline(str);
	if (!str)
	{
		rl_clear_history();
		write(STDERR_FILENO, "exit\n", 5);
		exit_mini(data, NULL);
	}
	return (str);
}

void	loop_utils(t_mdata *data, char *cmd)
{
	if (cmd != NULL)
	{
		split_parse(data, cmd);
		redir(data);
		if (data->nb_cmd > 1)
			if (check_line_pipe(data, data->cmd) == -1)
				return ;
		printf("nbcmd: %i\n", data->nb_cmd);
		if (data->nb_cmd == 1)
			launch_cmd(data, data->cmd);
		else if (data->nb_cmd > 1)
			mpipex(data);
	}
	reset_redir(data);
}

void	loop(t_mdata *data, char *cmd)
{
	data->block = 0;
	data->nb_cmd = 0;
	cmd = get_readline(data, "Minishell> ");
	if (*cmd && is_line_good(cmd) == 1)
	{
		add_history(cmd);
		data->cmd = NULL;
		if (is_unallowed_char(data, cmd) == 0)
		{
			if (cmd != NULL && ft_strlen(cmd) > 4096)
				ft_error(data, "Error: line too long\n", 127);
			else
				loop_utils(data, cmd);
		}
	}
	end_loop(data);
	free (cmd);
	cmd = NULL;
}

void	prompt(t_mdata *data, char **env)
{
	char	*cmd;

	cmd = NULL;
	data->cmd = NULL;
	env_setup(data, env);
	setup_pwd(data, env, 1);
	data->paths = NULL;
	while (1)
	{
		data->stdin_back = dup(STDIN_FILENO);
		data->stdout_back = dup(STDOUT_FILENO);
		setup_path(data);
		if (do_line_exist(data->env, "PWD") == -1)
			add_pwd(data);
		loop(data, cmd);
	}
}
