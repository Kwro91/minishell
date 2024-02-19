/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:32:02 by besalort          #+#    #+#             */
/*   Updated: 2024/02/19 15:49:44 by besalort         ###   ########.fr       */
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

void	close_here_doc(void)
{
	int	fd;

	fd = open(".here_doc_tmp", O_RDONLY);
	if (fd >= 0)
	{
		close(fd);
		unlink(".here_doc_tmp");
	}
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
		close_here_doc();
		free_files(tmp); //ici prob peut etre
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
