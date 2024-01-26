/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:29:29 by besalort          #+#    #+#             */
/*   Updated: 2024/01/26 13:58:04 by besalort         ###   ########.fr       */
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
		ft_error(data, "Error : malloc\n", 1);
	return (file);
}

t_files	*get_new_file(t_mdata *data, char *line, int here_doc)
{
	t_files	*new;

	new = malloc(sizeof(t_files));
	if (!new)
		ft_error(data, "Error: malloc\n", 1);
	new->here_doc = here_doc;
	new->files = next_word(line);
	new->next = NULL;
	return (new);
}

t_files	*create_new_files(t_mdata *data, t_files *files, char *line, int hd)
{
	t_files	*new;
	t_files	*tmp;

	new = get_new_file(data, line, 0);
	tmp = files;
	if (hd == 1)
		new->here_doc = 1;
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

void	is_fd_out(t_mdata *data, t_command *cmd)
{
	int		i;
	int		quote;
	int		squote;

	i = 0;
	quote = -1;
	squote = -1;
	if (!cmd)
		return ;
	while (cmd->line[i])
	{
		if (cmd->line[i] == '"')
			quote *= -1;
		if (cmd->line[i] == '\'')
			squote *= -1;
		if (cmd->line[i] == '>' && cmd->line[i + 1]
			&& quote == -1 && squote == -1)
			cmd->out = create_new_files(data, cmd->out, &cmd->line[i + 1], 0);
		i++;
	}
}

void	is_fd_in(t_mdata *data, t_command *cmd)
{
	int			i;
	t_quotes	quote;

	i = 0;
	quote.quote = -1;
	quote.squote = -1;
	while (cmd->line[i])
	{
		if (cmd->line[i] == '"')
			quote.quote *= -1;
		if (cmd->line[i] == '\'')
			quote.squote *= -1;
		if (cmd->line[i] == '<' && cmd->line[i + 1]
			&& quote.quote == -1 && quote.squote == -1)
		{
			if (cmd->line[i + 1] == '<')
			{
				i++;
				cmd->in = create_new_files(data, cmd->in, &cmd->line[i + 1], 1);
			}
			else
				cmd->in = create_new_files(data, cmd->in, &cmd->line[i + 1], 0);
		}
		i++;
	}
}
