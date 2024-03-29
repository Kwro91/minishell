/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:11:42 by besalort          #+#    #+#             */
/*   Updated: 2024/02/22 18:00:20 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_pwd(t_mdata *data)
{
	char	**new;
	int		i;
	int		lines;

	i = 0;
	if (!data->pwd)
		return ;
	lines = nb_word(data->env);
	new = malloc(sizeof(char *) * (lines + 2));
	if (!new)
		return (ft_error(data, "Error: malloc\n", -1));
	while (i < lines)
	{
		if (data->env[i])
			new[i] = ft_strdup(data->env[i]);
		free(data->env[i]);
		i++;
	}
	new[i] = ft_strjoin("PWD=", data->pwd);
	new[i + 1] = NULL;
	free(data->env);
	data->env = new;
}

void	setup_pwd_env(t_mdata *data)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!data->pwd)
		return ;
	tmp = ft_strdup("PWD=");
	if (!data->env)
		return ;
	while (data->env[i] && (ft_strncmp(tmp, data->env[i], 4) != 0))
		i++;
	if (data->env[i])
		free(data->env[i]);
	data->env[i] = ft_strjoin(tmp, data->pwd);
	free(tmp);
}

void	setup_pwd(t_mdata *data, char **env, int first)
{
	char	pwd[150];

	(void)env;
	if (first == 1)
	{
		data->pwd = malloc(sizeof(char) * 1);
		data->pwd[0] = '\0';
	}
	if (data->pwd)
		free(data->pwd);
	if (!getcwd(pwd, 150))
		data->pwd = NULL;
	else
		data->pwd = ft_strdup(pwd);
	setup_pwd_env(data);
}

void	pwd(t_mdata *data)
{
	setup_pwd(data, data->env, 0);
	if (!data->pwd)
		ft_error(data, "pwd: error cannot access parent directories\n", 1);
	else
	{
		ft_printf("%s\n", data->pwd);
		g_retval = 0;
	}
}
