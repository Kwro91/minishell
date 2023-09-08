/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:55:35 by besalort          #+#    #+#             */
/*   Updated: 2023/09/08 16:06:03 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    env_setup(t_mdata *data, char **env)
{
	int	i;
	int	nb;

	i = 0;
	nb = nb_word(env);
	data->env = malloc(sizeof(char *) * nb + 1);
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		i++;
	}
	data->env[i] = NULL;
}

void	env_cmd(t_mdata *data)
{
	int i;

	i = 0;
	while (data->env[i])
	{
		ft_printf("%s\n", data->env[i]);
		i++;
	}
}