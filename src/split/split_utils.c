/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:51:19 by besalort          #+#    #+#             */
/*   Updated: 2024/02/19 20:05:52 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_dquote(t_mdata *data, char *line, int i)
{
	int	len;
	
	len = ft_strlen(line);
	i++;
	while (i < len && line)
	{
		if (line[i] == '"')
			return (i);
		i++;
		len = ft_strlen(line);
	}
	printf("test\n");
	return (ft_error(data, "Error: double quote not closed\n", 0), -2);
}

int	split_squote(t_mdata *data, char *line, int i)
{
	int	len;
	
	len = ft_strlen(line);
	i++;
	while (i < len && line)
	{
		if (line[i] == '\'')
			return (i);
		i++;
		len = ft_strlen(line);
	}
	return (ft_error(data, "Error: double quote not closed\n", 0), -2);
}
