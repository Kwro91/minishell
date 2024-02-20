/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:36:45 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 15:46:30 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_empty_quotes(t_mdata *data, char **line, int i)
{
	char	*new;

	new = NULL;
	if (*line && &line[0][i] == &line[0][i + 1])
	{
		if (&line[0][i + 2])
		{
			new = ft_strdup(&line[0][i + 2]);
			if (!line)
				return (ft_error(data, "Error: remove quote1\n", 0), 1);
		}
		else
		{
			new = ft_strdup("");
			if (!line)
				return (ft_error(data, "Error: remove quote1\n", 0), 1);
		}
		*line = new;
		return (1);
	}
	return (0);
}

void	get_removed(t_mdata *data, char **line, int i)
{
	char	*new;
	char	*first;
	char	*second;

	if (!line)
		return (ft_error(data, "Error: remove quote1\n", 0));
	first = "";
	second = "";
	if (i > 0 && &line[0][i - 1])
		first = ft_strndup(data, *line, i);
	if (!first)
		return (ft_error(data, "Error: remove quote2\n", 0));
	if (&line[0][i + 1])
		second = ft_strdup(&line[0][i + 1]);
	if (!second)
		return (ft_error(data, "Error: remove quote3\n", 0));
	new = ft_strjoin(first, second);
	if (!new)
		return (ft_error(data, "Error: remove quote4\n", 0));
	if (first && ft_strncmp(first, "", 1) != 0)
		free(first);
	if (second && ft_strncmp(second, "", 1) != 0)
		free(second);
	*line = new;
}

int	remove_dquote(t_mdata *data, char **line, int i)
{
	if (check_empty_quotes(data, line, i) == 1)
		return (i);
	get_removed(data, line, i);
	while (*line && line[0][i])
	{
		if (line[0][i] == '"')
			return (get_removed(data, line, i), i);
		i++;
	}
	return (i);
}

int	remove_squote(t_mdata *data, char **line, int i)
{
	if (check_empty_quotes(data, line, i) == 1)
		return (i);
	get_removed(data, line, i);
	while (*line && line[0][i])
	{
		if (line[0][i] == '\'')
			return (get_removed(data, line, i), i);
		i++;
	}
	return (i);
}

void	remove_quotes(t_mdata *data, char **line)
{
	int	i;
	int	len;

	i = 0;
	if (!line || !line[0])
		return ;
	len = ft_strlen(line[0]);
	while (i < len)
	{
		if (line[0][i] && line[0][i] == '"')
			i = remove_dquote(data, line, i);
		else if (line[0][i] && line[0][i] == '\'')
			i = remove_squote(data, line, i);
		i++;
		len = ft_strlen(line[0]);
	}
}
