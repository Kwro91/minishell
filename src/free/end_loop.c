/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:32:02 by besalort          #+#    #+#             */
/*   Updated: 2024/03/12 16:56:51 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_files(t_command *cmd)
{
	t_files	*tmp;
	t_files	*next;

	tmp = cmd->in;
	while (tmp)
	{
		ft_free_me(tmp->files);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	tmp = cmd->out;
	while (tmp)
	{
		ft_free_me(tmp->files);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	free_cmd(t_command *cmd)
{
	if (cmd->line)
		free(cmd->line);
	if (cmd->cmd)
		ft_free_lines(cmd->cmd);
}

void	close_here_doc(t_mdata *data, t_command	*cmd)
{
	int		fd;
	char	*name;

	name = get_hdoc_name(data, cmd);
	fd = open(name, O_RDONLY);
	if (fd >= 0)
	{
		close(fd);
		unlink(name);
		printf("unlink :%s:\n", name);
	}
	ft_free_me(name);
}

void	close_end(t_mdata *data)
{
	t_command	*tmp;
	t_command	*next;

	tmp = NULL;
	tmp = data->cmd;
	if (!data->cmd || !tmp)
		return ;
	while (tmp)
	{
		free_cmd(tmp);
		close_all_files(data, tmp);
		close_here_doc(data, tmp);
		free_files(tmp);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	data->cmd = NULL;
}

void	end_loop(t_mdata *data)
{
	close_end(data);
}
