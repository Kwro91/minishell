/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:18 by besalort          #+#    #+#             */
/*   Updated: 2023/11/29 17:43:54 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*modif_export(char *line)
{
	int	i;
	// char	*add;

	i = 0;
	// add = "=''";
	while (line && line[i])
	{
		if (line[i] == '=')
		{
			if (line[i + 1] != '\0')
				return (line);
			else
				return (ft_strjoin(line, "''"));
		}
		i++;
	}
	return (ft_strjoin(line, "=''"));
	
}
