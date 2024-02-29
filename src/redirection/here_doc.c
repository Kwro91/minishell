/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:06:24 by besalort          #+#    #+#             */
/*   Updated: 2024/02/29 13:25:12 by afontain         ###   ########.fr       */
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
	if (line && !ft_strlen(line))
		return (0);
	if (ft_strncmp(line, file->files, len) == 0)
		return (1);
	return (0);
}

void	ft_mhere_doc(t_mdata *data, t_files *file)
{
	char	*line;

	ft_meof(file);
	int stdin_copy = dup(STDIN_FILENO);
	file->fd = open(".here_doc_tmp",
			O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file->fd < 0)
	{
		unlink(".here_doc_tmp");
		return (ft_error(data, "Error, here_doc\n", 1));
	}
	signal(SIGINT, &handle_siginthere);
	while (1)
	{
		line = readline(">");
		if (is_eof(line, file) == 1)
			break ;
		write(file->fd, line, ft_strlen(line));
		write(file->fd, "\n", 1);
		free(line);
	}
	if (g_retval == 128)
	{
		dup2(stdin_copy, 0);
		handle_signals();
		close(stdin_copy);
		close(file->fd);
		file->fd = open(".here_doc_tmp", O_RDONLY);
		return ; //valeur de retour erreur pour CTRL-C
	}
	close(stdin_copy);
	free(line);
	close(file->fd);
	file->fd = open(".here_doc_tmp", O_RDONLY);
	handle_signals();
}