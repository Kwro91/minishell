/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:36:45 by besalort          #+#    #+#             */
/*   Updated: 2024/03/19 18:53:19 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	parse_quotes(t_mdata *data, char *line, int i, char c)
// {
// 	int	len;

// 	(void)data;
// 	len = ft_strlen(line);
// 	while (i < len && line)
// 	{
// 		if (line[i] == c)
// 			return (i);
// 		i++;
// 		len = ft_strlen(line);
// 	}
// 	return (-2);
// }

// int	check_empty_quotes(t_mdata *data, char **line, int i)
// {
// 	char	*new;

// 	new = NULL;
// 	if (*line && &line[0][i] == &line[0][i + 1])
// 	{
// 		if (&line[0][i + 2])
// 		{
// 			new = ft_strdup(&line[0][i + 2]);
// 			if (!line)
// 				return (ft_error(data, "Error: remove quote1\n", -1), 1);
// 		}
// 		else
// 		{
// 			new = ft_strdup("");
// 			if (!line)
// 				return (ft_error(data, "Error: remove quote1\n", -1), 1);
// 		}
// 		*line = new;
// 		return (1);
// 	}
// 	return (0);
// }

// int	remove_dquote(t_mdata *data, char **line, int i)
// {
// 	if (check_empty_quotes(data, line, i) == 1)
// 		return (i);
// 	if (parse_quotes(data, *line, i + 1, '"') == -2)
// 		return (i + 1);
// 	get_removed(data, line, i);
// 	while (*line && line[0][i])
// 	{
// 		if (line[0][i] == '"')
// 			return (get_removed(data, line, i), i);
// 		i++;
// 	}
// 	return (i);
// }

// int	remove_squote(t_mdata *data, char **line, int i)
// {
// 	if (check_empty_quotes(data, line, i) == 1)
// 		return (i);
// 	if (parse_quotes(data, *line, i + 1, '\'') == -2)
// 		return (i + 1);
// 	get_removed(data, line, i);
// 	while (*line && line[0][i])
// 	{
// 		if (line[0][i] == '\'')
// 			return (get_removed(data, line, i), i);
// 		i++;
// 	}
// 	return (i);
// }

// void	remove_quotes(t_mdata *data, char **line)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	if (!line || !line[0])
// 		return ;
// 	len = ft_strlen(line[0]);
// 	while (i < len)
// 	{
// 		if (line[0][i] && line[0][i] == '"')
// 			i = remove_dquote(data, line, i);
// 		else if (line[0][i] && line[0][i] == '\'')
// 			i = remove_squote(data, line, i);
// 		else
// 			i++;
// 		len = ft_strlen(line[0]);
// 	}
// }
