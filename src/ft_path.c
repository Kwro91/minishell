/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:06:15 by besalort          #+#    #+#             */
/*   Updated: 2024/02/23 18:27:38 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_path_mini(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_split(env[i] + 5, ':'));
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
		ft_free_mini(data);
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
