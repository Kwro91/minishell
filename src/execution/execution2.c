/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:52:02 by afontain          #+#    #+#             */
/*   Updated: 2024/03/22 17:16:36 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_access_mini(t_mdata *data, char *cmd)
{
	char	*tmp;
	char	*join;

	join = NULL;
	tmp = NULL;
	if (cmd != NULL && ft_strncmp(cmd, "\0", 1) != 0)
	{
		tmp = ft_strjoin("minishell: command not found222: ", cmd);
		join = ft_strjoin(tmp, "\n");
	}
	else
	{
		tmp = ft_strdup("minishell: command not found444: ");
		join = ft_strjoin(tmp, "\n");
	}
	ft_error(data, join, 127);
	ft_free_me(tmp);
	ft_free_me(join);
}

char	*ft_access_mini(t_mdata *data, t_command *cmd)
{
	char	*join;
	char	*tmp;
	int		i;

	i = 0;
	if (!cmd->cmd)
		return (NULL);
	if (ft_strncmp(cmd->cmd[0], "", 1) == 0)
		return (ft_error(data, "minishell: command not found: \n", 127), NULL);
	if (cmd->cmd[0] && access(cmd->cmd[0], X_OK) == 0)
		return (tmp = access_utils(data, cmd));
	while (cmd->cmd[0] && data->paths && data->paths[i])
	{
		tmp = ft_strjoin(data->paths[i], "/");
		join = ft_strjoin(tmp, cmd->cmd[0]);
		if (join && access(join, X_OK) == 0)
			return (ft_free_me(tmp), join);
		ft_free_me(join);
		ft_free_me(tmp);
		i++;
	}
	error_access_mini(data, cmd->cmd[0]);
	return (NULL);
}
