/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:11:42 by besalort          #+#    #+#             */
/*   Updated: 2023/12/13 15:33:05 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_pwd_env(t_mdata *data)
{
	char	*tmp;
	int		i;

	i = 0;
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
	(void)env;
	char pwd[150];

	if (first == 1)
	{
		data->pwd = malloc(sizeof(char) * 1);
		data->pwd[0] = '\0';
	}
	if (data->pwd)
		free(data->pwd);
    getcwd(pwd, 150);
	data->pwd = ft_strdup(pwd);
	if (!data->pwd)
		exit_mini(data);
	setup_pwd_env(data);
}

void    pwd(t_mdata *data)
{
	ft_printf("%s\n", data->pwd);
}