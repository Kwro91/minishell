/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by besalort          #+#    #+#             */
/*   Updated: 2024/02/02 15:43:37 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_mvar(t_mdata *data)
{
	if (data->eof)
		free(data->eof);
	data->eof = NULL;
	if (data->in)
		ft_free_files(data->in);
	data->in = NULL;
	if (data->out)
		ft_free_files(data->out);
	data->out = NULL;
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

void	loop(t_mdata *data, char *cmd)
{
	t_command *tmp;
	t_files *filein;
	t_files *fileout;
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
				filein = tmp->in;
				fileout = tmp->out;
				// printf("La ligne : %s\n", tmp->line);
				while (filein)
				{
					// printf("le in : %s\n", filein->files);
					filein = filein->next;
				}
				while (fileout)
				{
					// printf("le out : %s\n", fileout->files);
					fileout = fileout->next;
				}
				sub_files(data, tmp);
				tmp = tmp->next;
			}
			launch_cmd(data, data->cmd);
			// if (cmd != NULL)
			// 	ft_pipex(4, cmdtotal, data->env, data);
		}
		free (cmd);
		// Ici va falloir free les redir et les cmd
		setup_mvar(data);
	}
}

void	prompt(t_mdata *data, int ac, char **av, char **env)
{
	char	*cmd;

	(void)ac;
	(void)av;
	cmd = NULL;
	data->eof = NULL;
	data->in = NULL;
	data->out = NULL;
	// data->in.fd = 0;
	// data->out.fd = 1;
	data->paths = ft_path_mini(env);
	setup_mvar(data);
	env_setup(data, env);
	setup_pwd(data, env, 1);
	while (1)
		loop(data, cmd);
}
