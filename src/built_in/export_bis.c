/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:18 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 20:16:40 by afontain         ###   ########.fr       */
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
		return (-1);
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

int	reset_line(t_mdata *data, char **export, char *line)
{
	int	i;
	int	j;

	i = do_line_exist(export, line);
	j = check_export_line(data, line, 0);
	if (i != -1 && j == 0)
	{
		free(export[i]);
		export[i] = ft_strdup(line);
		return (i);
	}
	return (-1);
}

void	error_export(t_mdata *data, char *error)
{
	ft_error(data, "minishell: export: << ", 1);
	ft_error(data, error, 1);
	ft_error(data, " >> is not allowed\n", 1);
}

int	check_export_line(t_mdata *data, char *line, int show)
{
	(void)data;
	if (ft_isalpha(line[0]) == 0)
	{
		if (show == 1)
			error_export(data, line);
		return (-1);
	}
	g_retval = 0;
	return (0);
}
