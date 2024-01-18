/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:14:52 by besalort          #+#    #+#             */
/*   Updated: 2024/01/18 18:11:18 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_mdata *data, char *line, int close)
{
	int	i;

	i = 0;
	while (line[i])
	{
		write(2, &line[i], 1);
		i++;
	}
	if (close == 1)
		exit_mini(data);
}

void	ft_free_files(t_files *files)
{
	t_files	*tmp;

	tmp = files;
	while (tmp)
	{
		if (tmp->fd > 1)
			close(tmp->fd);
		if (tmp->files)
			free(tmp->files);
		free(tmp);
		tmp = tmp->next;
	}
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
	while (lines && lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

void	ft_free_mini(t_mdata *data)
{
	if (data->env != NULL)
		ft_free_lines(data->env);
	ft_free_lines(data->paths);
	free(data->pwd);
	rl_clear_history();
}
