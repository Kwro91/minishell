/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:18:32 by besalort          #+#    #+#             */
/*   Updated: 2024/02/05 15:54:36 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_in(t_mdata *data, t_files *in)
{
	t_files	*files;

	files = in;
	if (files)
	{
		while (files->next)
			files = files->next;
		if (dup2(files->fd, 0) < 0)
			return (ft_error(data, "Error: dup2\n", 1));
		close(files->fd);
	}
}

void	dup_out(t_mdata *data, t_files *out)
{
	t_files	*files;

	files = out;
	if (files)
	{
		while (files->next)
			files = files->next;
		if (dup2(files->fd, 1) < 0)
			return (ft_error(data, "Error: dup2\n", 1));
		close(files->fd);
	}
}

void	dup_me(t_mdata *data, t_files *in, t_files *out)
{
	t_files	*files;

	files = in;
	if (in && in->fd >= 0)
	{
		while (files->next)
			files = files->next;
		if (dup2(files->fd, 0) < 0)
			return (ft_error(data, "Error: dup2\n", 1));
		close(in->fd);
	}
	if (out && out->fd >= 0)
	{
		if (dup2(out->fd, 1) < 0)
			return (ft_error(data, "Error: dup2\n", 1));
		close(out->fd);
	}
}