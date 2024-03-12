/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:54:38 by besalort          #+#    #+#             */
/*   Updated: 2024/03/12 17:58:56 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_out_files(t_mdata *data, t_command *cmd)
{
	t_files	*tmp;

	(void)data;
	if (!cmd->out)
		return ;
	tmp = cmd->out;
	while (tmp)
	{
		if (tmp->here_doc == 0)
			tmp->fd = open(tmp->files, O_RDWR | O_TRUNC | O_CREAT,
					S_IRWXU);
		else
			tmp->fd = open(tmp->files, O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
		tmp = tmp->next;
	}
}

void	open_in_files(t_mdata *data, t_command *cmd)
{
	t_files	*tmp;

	if (cmd->in == NULL)
		return ;
	tmp = cmd->in;
	// signal(SIGINT, handle_sighere);
	while (tmp)
	{
		if (tmp->here_doc == 0)
			tmp->fd = open(tmp->files, O_RDONLY);
		else
			ft_mhere_doc(data, cmd, tmp);
		if (tmp->fd < 0)
		{
			cmd->good = -1;
			ft_error(data, "minishell: ", 1);
			ft_error(data, tmp->files, 1);
			ft_error(data, ": no such file or directory\n", 1);
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_open_mfiles(t_mdata *data, t_command *cmd)
{
	open_in_files(data, cmd);
	open_out_files(data, cmd);
}

t_files	*create_new_files(t_mdata *data, t_files *files, t_command *cmd, t_ifiles *i)
{
	t_files	*new;
	t_files	*tmp;

	new = get_new_file(data, cmd, i);
	tmp = files;
	new->here_doc = i->hd;
	if (!tmp)
		return (new);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (files);
}
