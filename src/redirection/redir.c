/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:38:43 by besalort          #+#    #+#             */
/*   Updated: 2024/02/19 20:12:21 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dup_word(t_mdata *data, char	*line, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * len + 1);
	if (!word)
		ft_error(data, "Error, malloc\n", 1);
	while (i < len && line[i])
	{
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

int	do_out_redir(t_mdata *data, t_command *cmd)
{
	t_files	*tmp;

	tmp = cmd->out;
	while (tmp)
	{
		if (tmp->next == NULL && tmp->fd >= 0)
		{
			if (dup2(tmp->fd, 1) < 0)
			{
				cmd->good = -1;
				return (ft_error(data, "Error: dup2\n", 0), -1);
			}
			close(tmp->fd);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	do_in_redir(t_mdata *data, t_command *cmd)
{
	t_files	*tmp;

	tmp = cmd->in;
	while (tmp)
	{
		if (tmp->next == NULL && tmp->fd >= 0)
		{
			if (dup2(tmp->fd, 0) < 0)
			{
				cmd->good = -1;
				return (ft_error(data, "Error: dup2\n", 0), -1);
			}
			close(tmp->fd);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redir(t_mdata *data, t_command *cmd)
{
	int	value;

	value = 0;
	ft_open_mfiles(data, cmd);
	if (cmd->in)
		value = do_in_redir(data, cmd);
	if (cmd->out)
		do_out_redir(data, cmd);
	ft_free_lines(cmd->cmd);
	cmd->cmd = split_cmd(data, cmd->line, ' ');
	if (!cmd->cmd)
	{
		ft_error(data, "Error: split\n", 0);
		cmd->good = -1;
	}
	return (value);
}
