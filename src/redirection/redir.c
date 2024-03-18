/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:38:43 by besalort          #+#    #+#             */
/*   Updated: 2024/03/18 18:58:01 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dup_word(t_mdata *data, t_command *cmd, int len, int i)
{
	char	*word;
	int		j;

	j = 0;
	word = malloc(sizeof(char) * len + 1);
	if (!word)
		ft_error(data, "Error, malloc\n", -1);
	while (j < len && cmd->line[i])
	{
		word[j] = cmd->line[i];
		i++;
		j++;
	}
	word[j] = '\0';
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
				return (ft_error(data, "Error: dup25\n", -1), -1);
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
			// char *itoa = ft_itoa(tmp->here_doc);
			// int i = 0;
			// ft_error(data, "tmp->files:", 0);
			// ft_error(data, tmp->files, 0);
			// ft_error(data, "fd:", 0);
			// ft_error(data, itoa, 0);
			// ft_free_me(itoa);
			// ft_error(data, "i=", 0);
			// ft_error(data, ft_itoa(i), 0);
			// ft_error(data, "\n", 0);
			if (fcntl(tmp->fd, F_GETFL) == -1) //FCT NON AUTORISEE A RETIRER !!!
			{
				ft_error(data, "le fichier est ferme:", 0);
				printf("%i", tmp->fd);
				ft_error(data, ":\n", 0);
			}
			if (dup2(tmp->fd, 0) < 0)
			{
				cmd->good = -1;
				return (ft_error(data, "Error: dup26\n", -1), -1);
			}
			close(tmp->fd);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	do_redir(t_mdata *data, t_command *cmd)
{
	int	value;

	value = 0;
	if (cmd->in)
		value = do_in_redir(data, cmd);
	if (cmd->out)
		do_out_redir(data, cmd);
	return (value);
}

int	redir(t_mdata *data, t_command *cmd)
{
	ft_open_mfiles(data, cmd);
	return (0);
}
