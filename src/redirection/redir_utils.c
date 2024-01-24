/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:54:38 by besalort          #+#    #+#             */
/*   Updated: 2024/01/24 15:48:49 by besalort         ###   ########.fr       */
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
		tmp->fd = open(tmp->files, O_RDWR | O_TRUNC | O_CREAT,
			S_IRWXU);
		// printf("On open %s en out file\n", tmp->files);
		tmp = tmp->next;
	}
}

void	open_in_files(t_mdata *data, t_command *cmd)
{
	t_files	*tmp;

	if (cmd->in == NULL)
		return ;
	tmp = cmd->in;
	while (tmp)
	{
		if (tmp->here_doc == 0)
		{
			tmp->fd = open(tmp->files, O_RDONLY);
			// printf("On open %s en in file\n", tmp->files);
		}
		else
		{
			tmp->fd = open(".here_doc_tmp",
			O_CREAT | O_WRONLY | O_TRUNC, 0000644);
			// printf("On open un here_doc avec %s en EOF\n", tmp->files);
		}
		if (tmp->fd < 0)
		{
			ft_error(data, "minishell: ", 0);
			ft_error(data, tmp->files, 0);
			ft_error(data, ": no such file or directory\n", 0);
		}
		tmp = tmp->next;
	}
}

void	ft_open_mfiles(t_mdata *data, t_command *cmd)
{
	// if (data->here_doc == 0)
	open_in_files(data, cmd);
	// else
	// 	tmp->fd = open(".here_doc_tmp",
	// 		O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	open_out_files(data, cmd);
}

int	get_count(t_mdata *data, int count)
{
	(void)data;
	(void)count;
	// if (data->here_doc == 1)
	// {
	// 	count += 2;
	// 	count += ft_strlen(data->eof);
	// }
	// if (data->in.files != NULL)
	// {
	// 	count++;
	// 	count += ft_strlen(data->in.files);
	// }
	// if (data->out.files != NULL)
	// {
	// 	count++;
	// 	count += ft_strlen(data->out.files);
	// }
	// printf("count = %i\n", count);
	return (count);
}

char	*redir_rewrite(t_mdata *data, t_command *cmd)
{
	int	count;

	count = 0;
	get_count(data, count);
	return (cmd->line);
}
