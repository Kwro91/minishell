/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:18 by besalort          #+#    #+#             */
/*   Updated: 2024/02/07 17:13:12 by besalort         ###   ########.fr       */
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
	return (i);
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

void	error_export(t_mdata *data, char *error)
{
	ft_error(data, "minishell: export: << ", 0);
	ft_error(data, error, 0);
	ft_error(data, " >> is not allowed\n", 0);
}

int	check_export_line(t_mdata *data, char *line)
{
	(void)data;
	if (ft_isalpha(line[0]) == 0)
		return (-1);
	return (0);
}