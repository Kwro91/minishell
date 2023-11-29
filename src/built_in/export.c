/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:54:46 by besalort          #+#    #+#             */
/*   Updated: 2023/11/29 17:36:07 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_export(t_mdata *data, char *line, int i)
{
	char	**new;
	int		j;

	j = 0;
	while (data->export && data->export[i])
			i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return ;
	while (j < i)
	{
		new[j] = ft_strdup(data->export[j]);
		j++;
	}
	new[j] = ft_strdup(modif_export(line));
	new[j + 1] = NULL;
	ft_free_lines(data->export);
	data->export = new;
}

void	init_export(t_mdata *data, char *line)
{
	int	i;

	i = 0;
	if (!line)
		return ;
	if (!data->export)
	{
		data->export = malloc(sizeof(char *) * 2);
		data->export[0] = ft_strdup(modif_export(line));
		data->export[1] = NULL;	
	}
	else
		copy_export(data, line, i);
}

void	print_export(t_mdata *data)
{
	int	i;
	
	i = 0;
	while (data->export && data->export[i])
	{
		ft_printf("%s\n", data->export[i]);
		i++;
	}
}

void	export_cmd(t_mdata *data, char *line)
{
	if (!line)
		return (print_export(data));
	if (line != NULL)
		return (init_export(data, line));
}