/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:54:46 by besalort          #+#    #+#             */
/*   Updated: 2023/12/29 16:48:03 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_add(char **base, char **add, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (base[j] != NULL)
		j++;
	while (i < size && add[i])
	{
		if (reset_line(base, add[i]) == -1)
		{
			base[j] = ft_strdup(add[i]);
			j++;
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
	new = copy_add(new, data->export, base);
	new = copy_add(new, line, count_l);
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
	if (!data->export)
		copy_export(data, &line[1], 0);
	else
	{
		while (line[i])
		{
			 if (do_line_exist((data->export), line[i]) > -1)
				count++;
			i++;
		}
		copy_export(data, &line[1], count);
	}
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