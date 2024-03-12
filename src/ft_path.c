/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:06:15 by besalort          #+#    #+#             */
/*   Updated: 2024/03/07 17:28:49 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_path(t_mdata *data)
{
	if (data->paths)
		ft_free_lines(data->paths);
	data->paths = ft_path_mini(data);
}

char	**ft_path_mini(t_mdata *data)
{
	int		i;

	i = 0;
	while (data->env && data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
			return (ft_split(data->env[i] + 5, ':'));
		i++;
	}
	i = 0;
	while (data->export && data->export[i])
	{
		if (ft_strncmp(data->export[i], "PATH=", 5) == 0)
			return (ft_split(data->export[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

void	ft_path_no_env(t_mdata *data)
{
	data->paths = ft_calloc(sizeof(char *), 2);
	if (!data->paths)
		ft_free_mini(data);
	data->paths[0] = ft_strdup("");
	if (!data->paths[0])
		ft_free_mini(data);
	data->paths[1] = NULL;
}

void	ft_path_all(t_mdata *data, char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return (ft_path_no_env(data));
	while (paths[i])
		i++;
	data->paths = ft_calloc(sizeof(char *), (i + 1));
	if (!data->paths)
		ft_error(data, "Error: calloc\n", -1);
	if (paths == NULL || *paths == NULL)
		return ;
	i = 0;
	while (paths[i])
	{
		data->paths[i] = ft_strdup(paths[i]);
		if (!data->paths[i])
			return (ft_free_mini(data));
		free(paths[i]);
		i++;
	}
	data->paths[i] = NULL;
	if (paths)
		free(paths);
}
