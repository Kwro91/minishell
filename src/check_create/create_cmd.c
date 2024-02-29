/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:22:53 by besalort          #+#    #+#             */
/*   Updated: 2024/02/29 17:43:11 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*create_command(t_mdata *data, char *lines, int i)
{
	t_command	*new;

	new = NULL;
	new = malloc(sizeof(t_command));
	if (!new)
		ft_error(data, "Error: malloc", -1);
	new->line = ft_strdup(lines);
	new->good = 0;
	new->in = NULL;
	new->out = NULL;
	new->cmd = NULL;
	new->nb = i;
	is_fd_in(data, new);
	is_fd_out(data, new);
	new->next = NULL;
	return (new);
}

char	**get_split(t_mdata *data, char *line)
{
	char	**split;
	char	*cmp;

	cmp = ft_strdup("|\0");
	split = split_cmd(data, line, cmp);
	ft_free_me(cmp);
	return (split);
}

void	split_parse(t_mdata *data, char *line)
{
	t_command	*new;
	char		**split;
	int			i;

	new = NULL;
	i = 0;
	split = get_split(data, line);
	while (split && split[i])
	{
		if (i == 0)
		{
			new = create_command(data, split[i], i);
			data->cmd = new;
		}
		else
		{
			new->next = create_command(data, split[i], i);
			new = new->next;
		}
		i++;
	}
	data->nb_cmd = i;
	ft_free_lines(split);
}
