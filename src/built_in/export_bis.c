/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:18 by besalort          #+#    #+#             */
/*   Updated: 2023/12/01 16:52:39 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nb_char_equal(char	*line)
{
	int	i;
	
	i = 0;
	if (!line)
		return (0);
	while (line[i] && ft_isalnum(line[i]) == 1)
		i++;
	return(i);
}

int	do_line_exist(char **export, char *line)
{
	int	i;
	int	len_a;
	int	len_b;

	i = 0;
	if (export == NULL || !line)
		return (0);
	len_b = nb_char_equal(line);
	while (export[i])
	{
		len_a = nb_char_equal(export[i]);
		if (len_a == len_b)
		{
			if (ft_strncmp(export[i], line, len_b) == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}

int	reset_line(char **export, char *line)
{
	int	i;
	
	i = 0;
	i = do_line_exist(export, line);
	if (i != -1)
	{
		free(export[i]);
		export[i] = ft_strdup(line);
		return (i);
	}
	return (-1);
}

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
	new = ft_calloc(sizeof(char *), (nb_word(line) + 1));
	if (!new)
		return (NULL);
	while (line && line[i])
	{
		new[i] = ft_strdup(modif_utils(line[i]));
		i++;
	}
	new[i] = NULL;
	return (new);
}
