/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:51:40 by besalort          #+#    #+#             */
/*   Updated: 2024/01/11 16:22:36 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_load_av(t_pipex *data, int ac, char **av)
{
	data->file1.file = av[0];
	data->file2.file = av[ac - 1];
}

void	ft_listload(t_pipex *data, char **av)
{
	int	moving;

	moving = 1;
	if (data->here_doc == 1)
		moving = 2;
	data->lst = createlist(data->cmds, av + moving);
}

void	ft_load_env(t_pipex *data, char **env)
{
	char	*envbis;

	envbis = "";
	if (*env)
		data->data.env = env;
	else
	{
		data->data.env = malloc(sizeof(char *) * 2);
		if (!data->data.env)
		{
			free(data->data.env[0]);
			free(data->data.env[1]);
			return (free(data->data.env));
		}
		data->data.env[0] = ft_strdup(envbis);
		data->data.env[1] = NULL;
		data->is_env = -1;
	}
}

void	ft_load_values(t_pipex *data, int ac, char **av)
{
	data->data.ac = ac;
	data->data.av = av;
	if (ft_check_here_doc(data) != 0)
	{
		data->cmds = ac - 2;
		data->here_doc = 0;
	}
	else
	{
		data->cmds = ac - 3;
		data->here_doc = 1;
		ft_here_doc(data);
	}
}

int	ft_load(t_pipex *data, int ac, char **av, char **env)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (!av[i])
			return (-1);
		i++;
	}
	ft_load_values(data, ac, av);
	ft_listload(data, av);
	ft_load_av(data, ac, av);
	ft_load_env(data, env);
	return (1);
}
