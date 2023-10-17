/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:55:35 by besalort          #+#    #+#             */
/*   Updated: 2023/10/17 16:42:57 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    env_setup(t_mdata *data, char **env)
{
	int	i;
	int	nb;

	i = 0;
	nb = nb_word(env);
	if (nb > 0)
		data->env = malloc(sizeof(char *) * nb + 1);
	else
	{
		data->env = malloc(sizeof(char *) * 1);
		data->env = NULL;
	}
	if (!data->env)
	{
		ft_free_mini(data);
		exit(0);
	}
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