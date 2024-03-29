/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:30:43 by besalort          #+#    #+#             */
/*   Updated: 2024/02/23 19:13:08 by afontain         ###   ########.fr       */
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
char	*verif_cd(t_mdata *data, char *line)
{
	if (!line || ft_strncmp(line, "~\0", 2) == 0)
		return (return_home(data));
	else if (ft_strncmp(line, "-\0", 2) == 0)
		return (pwd(data), NULL);
	return (NULL);
}

void	cd_cmd(t_mdata *data, char *line)
{
	char	*modif;

	modif = NULL;
	modif = verif_cd(data, line);
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
		if (access(line, F_OK) == -1)
			ft_error(data, "Error: no such file or directory\n", 1);
		else if (access(line, R_OK | X_OK | W_OK) == -1)
			ft_error(data, "Error: not a directory\n", 1);
		else if (line && chdir(line) != 0 && (ft_strncmp(line, "-\0", 2) != 0))
			ft_error(data, "Error: no such file or directory\n", 1);
		else if (!line)
			ft_error(data, "Error: no such file or directory\n", 1);
	}
	ft_free_me(modif);
	setup_pwd(data, data->env, 0);
}
