/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:29:29 by besalort          #+#    #+#             */
/*   Updated: 2024/01/18 18:31:00 by besalort         ###   ########.fr       */
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

t_files	*get_new_file(char *line, int here_doc)
{
	t_files	*new;

	new = malloc(sizeof(t_files));
	new->here_doc = here_doc;
	new->files = next_word(line);
	new->next = NULL;
	return (new);
}

int	is_fd_out(t_mdata *data, char *line)
{
	int	i;
	int	value;
	t_files	*tmp;

	i = 0;
	value = 0;
	// data->out.files = size_my_file(data, line, '>');
	while (line[i])
	{
		if (line[i] == '>' && line[i + 1])
		{
			if (value == 0)
			{
				tmp = get_new_file(&line[i + 1], 0);
				data->out = tmp;
			}
			else
			{
				tmp->next = get_new_file(&line[i + 1], 0);
				tmp = tmp->next;
			}
			value++;
		}
		i++;
	}
	return (value);
}

int	is_fd_in(t_mdata *data, char *line)
{
	int	i;
	int	value;
	t_files	*tmp;

	i = 0;
	value = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1])
		{
			if (value == 0)
			{
				if (line[i + 1] == '<')
				{
					i++;
					tmp = get_new_file(&line[i + 1], 1);
				}
				else
					tmp = get_new_file(&line[i + 1], 0);
				data->in = tmp;
			}
			else
			{
				if (line[i + 1] == '<')
				{
					i++;
					tmp = get_new_file(&line[i + 1], 1);
				}
				else
					tmp = get_new_file(&line[i + 1], 0);
				tmp = tmp->next;
			}
			value++;
		}
		i++;
	}
	
	return (value);
}