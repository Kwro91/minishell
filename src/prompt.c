/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by besalort          #+#    #+#             */
/*   Updated: 2024/03/19 15:32:13 by besalort         ###   ########.fr       */
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

void	delete_files_names(t_mdata *data)
{
	t_command	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		sub_files(data, tmp);
		tmp = tmp->next;
	}
}

void	loop_utils(t_mdata *data, char *cmd)
{
	if (cmd != NULL)
	{
		split_parse(data, cmd);
		// if (data->cmd->line == NULL)
		// 	return ;
		if (data->nb_cmd > 1)
			if (check_line_pipe(data, data->cmd) == -1)
				return ;
		// delete_files_names(data);
		if (data->nb_cmd == 1)
			launch_cmd(data, data->cmd);
		else if (data->nb_cmd > 1)
			mpipex(data);
	}
	reset_redir(data);
}

void	loop(t_mdata *data, char *cmd)
{
	data->nb_cmd = 0;
	cmd = get_readline(data, "Minishell> ");
	if (*cmd && is_line_good(cmd) == 1)
	{
		add_history(cmd);
		data->cmd = NULL;
		if (is_unallowed_char(data, cmd) == 0)
			loop_utils(data, cmd);
		ft_error(data, "ICI ON CLOSE TOUT\n",0);
		end_loop(data);
	}
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
