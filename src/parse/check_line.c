/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:12:09 by besalort          #+#    #+#             */
/*   Updated: 2024/01/24 17:42:15 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_allowed(char c)
{
	char	*string;
	int		i;

	i = 0;
	string = (" \"'<>?|$");
	while (string && string[i])
	{
		if (c == string[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_before(t_mdata *data, char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_isalnum((int)line[i]) == 0 && is_allowed(line[i]) == 0)
		{
			ft_error(data, "Please don't use special character\n", 0);
			return (0);
		}
		i++;
	}
	return (1);
}
