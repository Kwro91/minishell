/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:22:53 by besalort          #+#    #+#             */
/*   Updated: 2024/01/23 15:45:29 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*create_command(t_mdata *data, char *lines)
{
	t_command	*new;
	int			i;

	i = 0;
	new = malloc(sizeof(t_command));
	if (!new)
		ft_error(data, "Error: malloc", 1);
	new->line = ft_strdup(lines);
	//on choppe les fd_in
	//on choppe les fd_out
	//on formate la ligne et on la split pour la preparer a execve dans new->cmd
	return (new);
}

t_command	*split_parse(t_mdata *data, char *line)
{
	t_command	*new;
	t_command	*tmp;
	char		**split;
	int			i;

	&tmp = &new;
	i = 0;
	split = ft_split(line, '|');
	while (split && split[i])
	{
		if (i == 0)
			tmp = create_command(split[i++]);
		else
		{
			tmp->next = create_command(split[i++]);
			tmp = tmp->next;
		}
	}
	return (new);
}