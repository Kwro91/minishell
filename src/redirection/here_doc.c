/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:06:24 by besalort          #+#    #+#             */
/*   Updated: 2024/02/06 17:45:44 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_meof(t_files *file)
{
	char	*eof;
	char	*add;

	add = "\n";
	eof = ft_strdup(file->files);
	free(file->files);
	file->files = ft_strjoin(eof, add);
	free(eof);
}

void	ft_mhere_doc(t_mdata *data, t_files *file)
{
	char	*line;

	ft_meof(file);
	file->fd = open(".here_doc_tmp",
			O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file->fd < 0)
	{
		unlink(".here_doc_tmp");
		return (ft_error(data, "Error, here_doc\n" , 0));
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (ft_strncmp(line, file->files, ft_strlen(file->files)) == 0)
			break ;
		write(file->fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(file->fd);
	file->fd = open(".here_doc_tmp", O_RDONLY);
}
