/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:54:46 by besalort          #+#    #+#             */
/*   Updated: 2024/02/07 19:32:07 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_add(t_mdata *data, char **base, char **add, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (base[j] != NULL)
		j++;
	while (add && add[i] && i < size)
	{
		if (reset_line(data, base, add[i]) == -1)
		{
			if (check_export_line(data, add[i], 0) == 0)
			{
				base[j] = ft_strdup(add[i]);
				j++;
			}
		}
		i++;
	}
	return (base);
}

void	copy_export(t_mdata *data, char **line, int count)
{
	char	**new;
	int		base;
	int		count_l;

	base = nb_word(data->export);
	count_l = nb_word(line);
	new = ft_calloc(sizeof(char *), (base + (count_l - count) + 1));
	if (!new)
		return ;
	new = copy_add(data, new, data->export, base);
	new = copy_add(data, new, line, count_l);
	new[base + (count_l - count)] = NULL;
	ft_free_lines(data->export);
	data->export = new;
}

void	init_export(t_mdata *data, char **line)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	if (!line)
		return ;	
	while (line[i])
	{
		if (check_export_line(data, line[i], 1) == -1
			|| do_line_exist((data->export), line[i]) > -1)
			count++;
		i++;
	}
	copy_export(data, &line[1], count);
}

void	print_export(t_mdata *data)
{
	int	i;

	i = 0;
	if (!data->export)
		return ;
	while (data->export && data->export[i])
	{
		ft_printf("export ");
		good_print(data->export[i]);
		ft_printf("\n");
		i++;
	}
}

void	export_cmd(t_mdata *data, char **line)
{
	if (!line)
		return (print_export(data));
	if (line != NULL)
		return (init_export(data, line));
}
