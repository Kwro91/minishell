/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:34:45 by besalort          #+#    #+#             */
/*   Updated: 2024/03/26 16:35:06 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_dq_line(t_mdata *data, char *line, int i)
{
	int	len;

	len = ft_strlen(line);
	while (i < len && line)
	{
		if (line[i] == '"')
			return (i);
		i++;
	}
	data->block = 1;
	return (ft_error(data, "Error: double quote not closed\n", 2), -2);
}

int	parse_sq_line(t_mdata *data, char *line, int i)
{
	int	len;

	len = ft_strlen(line);
	while (i < len && line)
	{
		if (line[i] == '\'')
			return (i);
		i++;
	}
	data->block = 1;
	return (ft_error(data, "Error: simple quote not closed\n", 2), -2);
}

int	parse_line(t_mdata *data, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			i = parse_dq_line(data, str, i + 1);
		else if (str[i] == '\'')
			i = parse_sq_line(data, str, i + 1);
		if (i < 0)
			return (i);
		i++;
	}
	return (i);
}
