/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:55:35 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 20:16:11 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_setup(t_mdata *data, char **env)
{
	int	i;
	int	nb;

	i = 0;
	nb = nb_word(env);
	if (nb >= 0)
		data->env = malloc(sizeof(char *) * (nb + 1));
	else
		data->env = NULL;
	if (!data->env)
		exit_mini(data);
	while (i < nb)
	{
		data->env[i] = ft_strdup(env[i]);
		i++;
	}
	data->env[i] = NULL;
}

void	env_cmd(t_mdata *data)
{
	int	i;

	i = 0;
	if (!data->env)
		return ;
	while (data->env && data->env[i])
	{
		ft_printf("%s\n", data->env[i]);
		i++;
	}
	i = 0;
	while (data->export && data->export[i])
	{
		ft_printf("%s\n", data->export[i]);
		i++;
	}
	g_retval = 0;
}
