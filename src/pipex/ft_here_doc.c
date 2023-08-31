/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:41:29 by besalort          #+#    #+#             */
/*   Updated: 2023/07/06 16:43:46 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_here_doc(t_pipex *data)
{
	char	*s1;
	char	*s2;
	int		cmp;

	s1 = ft_strdup(data->data.av[1]);
	s2 = "here_doc";
	cmp = ft_strncmp(s1, s2, ft_strlen(s1));
	free(s1);
	return (cmp);
}

void	ft_eof(t_pipex *data)
{
	char	*eof;
	char	*newline;

	newline = "\n";
	eof = ft_strdup(data->data.av[2]);
	data->eof = ft_strjoin(eof, newline);
	free(eof);
}

void	ft_here_doc(t_pipex *data)
{
	char	*line;

	ft_eof(data);
	data->file1.fd = open(".here_doc_tmp",
			O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (data->file1.fd < 0)
	{
		unlink(".here_doc_tmp");
		ft_msg("Error, here_doc\n");
	}
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		if (ft_strncmp(line, data->eof, ft_strlen(data->eof)) == 0)
			break ;
		write(data->file1.fd, line, ft_strlen(line));
		write(data->file1.fd, "\n", 1);
		free(line);
	}
	free(line);
	free(data->eof);
	close(data->file1.fd);
}
