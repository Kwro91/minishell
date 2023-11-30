/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:18 by besalort          #+#    #+#             */
/*   Updated: 2023/11/30 17:26:56 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	reset_line()
// {
	
// }

char	*modif_utils(char *line)
{
	int	i;

	i = 0;
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


char	**modif_export(char **line)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc(sizeof(char *) * (nb_word(line) + 1));
	if (!new)
		return (NULL);
	while (line && line[i])
	{
		new[i] = ft_strdup(modif_utils(line[i]));
		i++;
	}
	// ft_free_lines(line);
	new[i] = NULL;
	return (new);
}
