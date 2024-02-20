/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:48:11 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 15:56:38 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_redir(t_mdata *data)
{
	if (!isatty(STDIN_FILENO))
		if (dup2(data->stdin_back, STDIN_FILENO) < 0)
			return (ft_error(data, "Error: dup21111\n", 1));
	if (!isatty(STDOUT_FILENO))
		if (dup2(data->stdout_back, STDOUT_FILENO) < 0)
			return (ft_error(data, "Error: dup22222\n", 1));
}
