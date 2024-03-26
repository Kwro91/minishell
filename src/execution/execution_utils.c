/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:26:57 by besalort          #+#    #+#             */
/*   Updated: 2024/03/26 15:17:12 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	loop_directory(t_mdata *data, t_command *cmd, char *path, DIR *dir)
{
	if (path && access(path, F_OK) != -1)
	{
		if (dir != NULL)
		{
			closedir(dir);
			cmd->good = -1;
			ft_error(data, "minishell : ", 126);
			ft_error(data, path, 126);
			ft_error(data, ": is a directory\n", 126);
		}
	}
}

char	*access_utils(t_mdata *data, t_command *cmd)
{
	char	*tmp;

	tmp = ft_strdup(cmd->cmd[0]);
	if (!tmp)
		ft_error(data, "Error: strdup\n", -1);
	return (tmp);
}
