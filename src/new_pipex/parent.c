/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:38:09 by besalort          #+#    #+#             */
/*   Updated: 2024/02/02 17:53:16 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rfirst(t_mdata * data, t_command *cmd)
{
	if (pipe(data->pipes) < 0)
		return ("Error: pipe\n", ft_exit(data), NULL);
}

t_command	*rmiddle(t_mdata *data, t_command *cmd)
{
	
}

void	rlast(t_mdata *data, t_command *cmd)
{
	
}

void	mwait_childs(t_mdata *data)
{
	int			status;
	int			count;
	t_command	*tmp;

	status = 0;
	count = 0;
	tmp = data->cmd;
	while (tmp)
	{
		waitpid(-1, &status, 0);
		if (count == 0)
		{
			close(data->pipes[1]);
			close(data->pipes[0]);
		}
		count++;
		tmp = tmp->next;
	}
}

void	run_all(t_mdata *data)
{
	t_command *tmp;

	tmp = data->cmd;
	rfist(data, tmp);
	tmp = tmp->next;
	tmp = rmiddle(data, tmp);
	rlast(data, tmp);
	mwait_childs(data);
}