/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:14:13 by besalort          #+#    #+#             */
/*   Updated: 2024/02/22 16:07:13 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isvisible(int c)
{
	if (c > 32 && c <= 126)
		return (1);
	return (0);
}

int	is_line_good(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i])
	{
		if (ft_isvisible(line[i]) == 1)
			return (1);
		i++;
	}
	return (-1);
}
