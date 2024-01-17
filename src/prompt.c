/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by besalort          #+#    #+#             */
/*   Updated: 2024/01/17 18:03:24 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_mvar(t_mdata *data)
{
	if (data->eof)
		free(data->eof);
	data->eof = NULL;
	if (data->in.files)
		ft_free_lines(data->in.files);
	data->in.files = NULL;
	if (data->out.files)
		ft_free_lines(data->out.files);
	data->out.files = NULL;
	if (data->in.fd > 0)
		close(data->in.fd);
	data->in.fd = 0;
	if (data->out.fd > 1)
		close(data->in.fd);
	data->out.fd = 1;
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

void	loop(t_mdata *data, char **env, char *cmd, char **cmdtotal)
{
	cmd = get_readline(data, "Minishell> ");
	if (*cmd && ft_strncmp(cmd, "/n", 2) != 0)
	{
		add_history(cmd);
		cmdtotal = ft_split(cmd, ' ');
		if (verif_cmd(data, cmdtotal, env) == 0)
		{
			if (cmd != NULL)
			{
				cmd = redir(data, cmd);
				launch_cmd(data, cmdtotal, env);
			}
			// if (cmd != NULL)
			// 	ft_pipex(4, cmdtotal, data->env, data);
		}
		free (cmd);
		// Ici va falloir free les redir aussi
		if (*cmdtotal)
			ft_free_lines(cmdtotal);
		setup_mvar(data);
	}
}

void	prompt(t_mdata *data, int ac, char **av, char **env)
{
	char	*cmd;
	char	**cmdtotal;

	(void)ac;
	(void)av;
	cmd = NULL;
	cmdtotal = NULL;
	data->eof = NULL;
	data->in.files = NULL;
	data->out.files = NULL;
	data->in.fd = 0;
	data->out.fd = 1;
	data->paths = ft_path_mini(env);
	setup_mvar(data);
	env_setup(data, env);
	setup_pwd(data, env, 1);
	while (1)
		loop(data, env, cmd, cmdtotal);
}
