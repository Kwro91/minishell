/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:14:52 by besalort          #+#    #+#             */
/*   Updated: 2024/02/22 17:14:23 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(t_mdata *data, char *line, int close)
{
	int	i;

	i = 0;
	g_retval = close;
	while (line[i])
	{
		write(2, &line[i], 1);
		i++;
	}
	if (close == -1)
		exit_mini(data, NULL);
}

void	ft_free_files(t_files *files)
{
	t_files	*tmp;

	tmp = files;
	while (tmp)
	{
		if (tmp->here_doc == 1)
			unlink(".here_doc_tmp");
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
	close(data->stdin_back);
	close(data->stdout_back);
	rl_clear_history();
}
