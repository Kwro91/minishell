/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:14:52 by besalort          #+#    #+#             */
/*   Updated: 2024/03/22 13:59:52 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(t_mdata *data, char *line, int close)
{
	g_retval = close;
	if (line)
		write(2, line, ft_strlen(line));
	if (close == -1)
		exit_mini(data, NULL);
}

void	ft_free_adr(void *adr)
{
	if (adr)
		free(adr);
	adr = NULL;
}

void	ft_free_lines(char	**lines)
{
	int	i;

	i = 0;
	if (lines == NULL)
		return ;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
	lines = NULL;
}

void	ft_free_mini(t_mdata *data)
{
	end_loop(data);
	if (data->env != NULL)
		ft_free_lines(data->env);
	ft_free_lines(data->paths);
	ft_free_lines(data->export);
	ft_free_lines(data->unset);
	free(data->pwd);
	rl_clear_history();
}
