/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:29:29 by besalort          #+#    #+#             */
/*   Updated: 2024/03/18 17:54:31 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**size_my_file(t_mdata *data, char *line, char c)
{
	int		i;
	int		count;
	char	**file;

	i = 0;
	count = 0;
	while (line[i + 1])
	{
		if (line[i] == c && line[i + 1] != c)
			count++;
		i++;
	}
	file = malloc(sizeof(char *) * count + 1);
	if (!file)
		ft_error(data, "Error : malloc\n", -1);
	return (file);
}

t_files	*get_new_file(t_mdata *data, t_command *cmd, t_ifiles *i)
{
	t_files	*new;

	new = malloc(sizeof(t_files));
	if (!new)
		ft_error(data, "Error: malloc\n", -1);
	new->fd = -1;
	new->here_doc = i->hd;
	new->files = next_word(data, cmd, i->i);
	new->next = NULL;
	// printf("\nNew file:\nfiles:%s:\nhere_doc:%i:\ni->i:%i:\nline:%s:\n", new->files, new->here_doc, i->i, cmd->line);
	return (new);
}

t_files	*get_fd_out(t_mdata *data, t_command *cmd, int i)
{
	t_ifiles	new;
	
	new.hd = 0;
	new.i = (i + 1);
	if (cmd->line[i + 1] == '>')
	{
		new.i += 1;
		new.hd = 1;
	}
	return (create_new_files(data, cmd->out, cmd, &new));
}

void	is_fd_out(t_mdata *data, t_command *cmd)
{
	int			i;
	t_quotes	quote;

	i = 0;
	quote.quote = -1;
	quote.squote = -1;
	if (!cmd)
		return ;
	while (cmd->line[i])
	{
		if (quote.squote == -1 && cmd->line[i] == '"')
			quote.quote *= -1;
		if (quote.quote == -1 && cmd->line[i] == '\'')
			quote.squote *= -1;
		if (cmd->line[i] == '>' && cmd->line[i + 1]
			&& quote.quote == -1 && quote.squote == -1)
		{
			cmd->out = get_fd_out(data, cmd, i);
			if (cmd->line[i + 1] == '>')
				i++;
		}
		i++;
	}
}

void	is_fd_in(t_mdata *data, t_command *cmd)
{
	t_quotes	quote;
	t_ifiles	new;

	quote.quote = -1;
	quote.squote = -1;
	new.i = 0;
	while (cmd->line[new.i])
	{
		new.hd = 0;
		if (quote.squote == -1 && cmd->line[new.i] == '"')
			quote.quote *= -1;
		if (quote.quote == -1 && cmd->line[new.i] == '\'')
			quote.squote *= -1;
		if (cmd->line[new.i] == '<' && cmd->line[new.i + 1]
			&& quote.quote == -1 && quote.squote == -1)
		{
			if (cmd->line[new.i + 1] == '<')
			{
				new.i += 1;
				new.hd = 1;
			}
			cmd->in = create_new_files(data, cmd->in, cmd, &new);
		}
		new.i++;
	}
}
