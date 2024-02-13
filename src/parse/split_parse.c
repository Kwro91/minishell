/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:22:53 by besalort          #+#    #+#             */
/*   Updated: 2024/02/13 18:19:06 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*create_command(t_mdata *data, char *lines)
{
	t_command	*new;

	new = NULL;
	new = malloc(sizeof(t_command));
	if (!new)
		ft_error(data, "Error: malloc", 1);
	new->line = ft_strdup(lines);
	new->good = 0;
	new->in = NULL;
	new->out = NULL;
	parse_cmd(data, new);
	new->cmd = NULL;
	// new->cmd = ft_split(new->line, ' ');
	// if (!new->cmd)
	// 	ft_error(data, "Error: malloc", 1);
	is_fd_in(data, new);
	is_fd_out(data, new);
	new->next = NULL;
	return (new);
}

void	split_parse(t_mdata *data, char *line)
{
	t_command	*new;
	char		**split;
	int			i;

	new = NULL;
	i = 0;
	split = ft_split(line, '|');
	while (split && split[i])
	{
		if (i == 0)
		{
			new = create_command(data, split[i++]);
			data->cmd = new;
		}
		else
		{
			new->next = create_command(data, split[i++]);
			new = new->next;
		}
	}
	data->nb_cmd = i;
	ft_free_lines(split);
}
