/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:06:15 by besalort          #+#    #+#             */
/*   Updated: 2023/07/04 17:01:27 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_path(char **env)
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

void	ft_path_no_environement(t_pipex *data)
{
	data->paths = ft_calloc(sizeof(char *), 2);
	if (!data->paths)
		ft_free(data);
	data->paths[0] = ft_strdup("");
	if (!data->paths[0])
		ft_free(data);
	data->paths[1] = NULL;
}

void	ft_path_complete(t_pipex *data, char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return (ft_path_no_environement(data));
	while (paths[i])
		i++;
	data->paths = ft_calloc(sizeof(char *), (i + 1));
	if (!data->paths)
		ft_free(data);
	if (paths == NULL || *paths == NULL)
		return ;
	i = 0;
	while (paths[i])
	{
		data->paths[i] = ft_strdup(paths[i]);
		if (!data->paths[i])
			return (ft_free_paths(paths), ft_free(data));
		free(paths[i]);
		i++;
	}
	data->paths[i] = NULL;
	if (paths)
		free(paths);
}
