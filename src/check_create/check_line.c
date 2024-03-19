/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:12:09 by besalort          #+#    #+#             */
/*   Updated: 2024/03/19 15:47:29 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_line_pipe(t_mdata *data, t_command *cmd)
{
	t_command	*tmp;
	int			good;
	int			i;

	tmp = cmd;
	while (tmp)
	{
		good = 0;
		i = 0;
		while (tmp->line[i] && good == 0)
		{
			if (tmp->line[i] > 32 && tmp->line[i] <= 126)
				good = 1;
			i++;
		}
		if (good == 0)
		{
			ft_error(data, "minishell: ", 2);
			ft_error(data, "syntax error near token ", 2);
			return (ft_error(data, "'|'\n", 2), -1);
		}
		tmp = tmp->next;
	}
	return (0);
}
