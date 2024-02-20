/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:06:24 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 20:03:12 by afontain         ###   ########.fr       */
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

int	is_eof(char	*line, t_files *file)
{
	int	len;

	len = ft_strlen(line);
	if ((int)ft_strlen(file->files) < len)
		len = (int)ft_strlen(file->files);
	if (ft_strncmp(line, file->files, len) == 0)
		return (1);
	return (0);
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
		return (ft_error(data, "Error, here_doc\n", 1));
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (is_eof(line, file) == 1)
			break ;
		write(file->fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(file->fd);
	file->fd = open(".here_doc_tmp", O_RDONLY);
}
