/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:18:32 by besalort          #+#    #+#             */
/*   Updated: 2024/02/06 12:20:24 by besalort         ###   ########.fr       */
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
	dup_in(data, in);
	dup_out(data, out);
}