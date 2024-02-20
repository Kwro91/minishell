/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:26:57 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 19:36:24 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*access_utils(t_mdata *data, t_command *cmd)
{
	char	*tmp;

	tmp = ft_strdup(cmd->cmd[0]);
	if (!tmp)
		ft_error(data, "Error: strdup\n", 1);
	return (tmp);
}
