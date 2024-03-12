/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:30:43 by besalort          #+#    #+#             */
/*   Updated: 2024/03/12 15:33:49 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*return_home(t_mdata *data)
{
	int	i;

	i = 0;
	if (!data->env)
		return (NULL);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "HOME=", 5) == 0)
			return (ft_strdup(&data->env[i][5]));
		i++;
	}
	return (NULL);
}

char	*verif_cd(t_mdata *data, char **cmd)
{
	if (!cmd || ft_strncmp(cmd[0], "~\0", 2) == 0)
		return (return_home(data));
	else if (ft_strncmp(cmd[0], "-\0", 2) == 0)
		return (pwd(data), NULL);
	return (NULL);
}

void	cd_cmd(t_mdata *data, char **cmd)
{
	char	*modif;

	modif = NULL;
	modif = verif_cd(data, cmd);
	if (modif)
	{
		if (chdir(modif) != 0)
			ft_error(data, "Error: chdir\n", 1);
		if (modif)
			free(modif);
		return (setup_pwd(data, data->env, 0));
	}
	else
	{
		if (access(cmd[0], F_OK) == -1)
			ft_error(data, "Error: no such file or directory\n", 1);
		else if (access(cmd[0], R_OK | X_OK | W_OK) == -1)
			ft_error(data, "Error: not a directory\n", 1);
		else if (cmd[0] && chdir(cmd[0]) != 0 && (ft_strncmp(cmd[0], "-\0", 2) != 0))
			ft_error(data, "Error: no such file or directory\n", 1);
		else if (!cmd[0])
			ft_error(data, "Error: no such file or directory\n", 1);
	}
	ft_free_me(modif);
	setup_pwd(data, data->env, 0);
}
