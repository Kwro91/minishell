/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:27:52 by afontain          #+#    #+#             */
/*   Updated: 2024/02/29 15:00:08 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_export_good(char	*line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '=')
			return (1);
		if (ft_isalnum(line[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}

int	check_export_value(char *var)
{
	int	i;

	i = nb_char_equal(var);
	if (var[i] == '=' && var[i + 1] != '\0')
		return (1);
	return (-1);
}
