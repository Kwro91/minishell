/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:38:43 by besalort          #+#    #+#             */
/*   Updated: 2024/02/12 15:49:36 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dup_word(char	*line, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * len + 1);
	while (i < len && line[i])
	{
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*next_word(char *line)
{
	int	i;
	int	count;
	int	apo;

	i = 0;
	apo = 0;
	count = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] == '"' && apo == 0)
		{
			apo = 1;
			i++;
		}
		if ((line[i] == '"' && apo == 1)
			|| (apo == 0 && ft_isalnum(line[i]) == 0))
			break ;
		i++;
		count++;
	}
	if (count == 0)
		return (NULL);
	return (dup_word(&line[i - count], count));
}

// int	is_here_doc(t_mdata *data, char *line)
// {
// 	int		i;
// 	t_files	*tmp;

// 	i = 0;
// 	if (data->eof)
// 		free(data->eof);
// 	while (line[i + 1])
// 	{
// 		if (line[i] == '<' && line[i + 1] == '<')
// 		{

// 			return (next_word(&line[i + 2]));
// 		}
// 		i++;
// 	}
// 	return (0);
// }

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
	cmd->cmd = ft_split(cmd->line, ' ');
	return (value);
}
