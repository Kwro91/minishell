/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by besalort          #+#    #+#             */
/*   Updated: 2024/02/15 17:55:01 by besalort         ###   ########.fr       */
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

void	loop_utils(t_mdata *data, t_command *tmp, char *cmd)
{
	if (cmd != NULL && check_before(data, cmd) == 1)
	{
		split_parse(data, cmd);
		if (data->nb_cmd > 1)
			if (check_line_pipe(data, data->cmd) == -1)
				return ;
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
	reset_redir(data);
}

void	loop(t_mdata *data, char *cmd)
{
	t_command	*tmp;

	tmp = NULL;
	data->nb_cmd = 0;
	cmd = get_readline(data, "Minishell> ");
	if (*cmd && ft_strncmp(cmd, "\n\0", 2) != 0)
	{
		add_history(cmd);
		data->cmd = NULL;
		loop_utils(data, tmp, cmd);
		end_loop(data);
		free (cmd);
		cmd = NULL;
		if (tmp)
			free (tmp);
	}
}

void	prompt(t_mdata *data, char **env)
{
	char	*cmd;

	cmd = NULL;
	data->paths = ft_path_mini(env);
	data->cmd = NULL;
	env_setup(data, env);
	setup_pwd(data, env, 1);
	data->stdin_back = dup(STDIN_FILENO);
	data->stdout_back = dup(STDOUT_FILENO);
	while (1)
	{
		if (do_line_exist(data->env, "PWD") == -1)
			add_pwd(data);
		loop(data, cmd);
	}
}
