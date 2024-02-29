/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:37:39 by besalort          #+#    #+#             */
/*   Updated: 2024/02/29 12:38:11 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *get_removed_first(t_mdata *data, char **line, int i)
{
    char    *first;

    first = NULL;
    if (i > 0 && &line[0][i + 1])
    {
        first = ft_strndup(data, *line, i);
        if (!first)
            return (ft_error(data, "Error: remove quote\n", -1), NULL);
    }
    return first;
}

char    *get_removed_second(t_mdata *data, char **line, int i)
{
    char    *second;

    second = NULL;
    if (&line[0][i + 1])
    {
        second = ft_strdup(&line[0][i + 1]);
        if (!second)
            return (ft_error(data, "Error: remove quote\n", -1), NULL);
    }
    return (second);
}

void    get_removed(t_mdata *data, char **line, int i)
{
    char    *new;
    char    *first;
    char    *second;

    if (!line)
        return (ft_error(data, "Error: remove quote\n", -1));
    first = get_removed_first(data, line, i);
    second = get_removed_second(data, line, i);
    if (first && second)
        new = ft_strjoin(first, second);
    else if (!first && second)
        new = ft_strdup(second);
    else if (first && !second)
        new = ft_strdup(second);
    else
        new = ft_strdup("");
    if (!new)
        return (ft_error(data, "Error: remove quote\n", -1));
    ft_free_me(first);
    ft_free_me(second);
    ft_free_me(line[0]);
    *line = new;
}
