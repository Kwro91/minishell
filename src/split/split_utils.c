/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:51:19 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 19:13:57 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_to_cmp(char c, char *cmp)
{
	int	i;

	i = 0;
	while (cmp && cmp[i])
	{
		if (cmp[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	split_dquote(t_mdata *data, char *line, int i)
{
	int	len;

	(void)data;
	len = ft_strlen(line);
	i++;
	while (i < len && line)
	{
		if (line[i] == '"')
			return (i);
		i++;
		len = ft_strlen(line);
	}
	// return (ft_error(data, "Error : double quote not closed\n", 0), -2);
	return (i);
}

int	split_squote(t_mdata *data, char *line, int i)
{
	int	len;

	(void)data;
	len = ft_strlen(line);
	i++;
	while (i < len && line)
	{
		if (line[i] == '\'')
			return (i);
		i++;
		len = ft_strlen(line);
	}
	// return (ft_error(data, "Error : single quote not closed\n", 0), -2);
	return (i);
}
