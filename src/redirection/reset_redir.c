/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:48:11 by besalort          #+#    #+#             */
/*   Updated: 2024/02/29 19:07:18 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_redir(t_mdata *data)
{
	if (!isatty(STDIN_FILENO))
	{
		if (dup2(data->stdin_back, STDIN_FILENO) < 0)
			return (ft_error(data, "Error: dup2_1\n", -1));
	}
	close(data->stdin_back);
	if (!isatty(STDOUT_FILENO))
	{
		if (dup2(data->stdout_back, STDOUT_FILENO) < 0)
			return (ft_error(data, "Error: dup2_2\n", -1));
	}
	close(data->stdout_back);
}
