/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by besalort          #+#    #+#             */
/*   Updated: 2024/02/06 13:10:20 by besalort         ###   ########.fr       */
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
	t_command *tmp;
	
	data->nb_cmd = 0;
	cmd = get_readline(data, "Minishell> ");
	if (*cmd && ft_strncmp(cmd, "/n", 2) != 0)
	{
		add_history(cmd);
		if (cmd != NULL && check_before(data, cmd) == 1)
		{
			data->cmd = NULL;
			split_parse(data, cmd);
			tmp = data->cmd;
			while (tmp)
			{
				sub_files(data, tmp);
				tmp = tmp->next;
			}
			launch_cmd(data, data->cmd);
			// if (cmd != NULL)
			// 	ft_pipex(4, cmdtotal, data->env, data);
		}
		free (cmd);
		// Ici va falloir free les redir et les cmd
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
		loop(data, cmd);
}
