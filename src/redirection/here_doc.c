/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:06:24 by besalort          #+#    #+#             */
/*   Updated: 2024/03/14 14:03:45 by besalort         ###   ########.fr       */
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

char	*get_hdoc_name(t_mdata *data, t_command *cmd)
{
	char	*name;
	char	*number;
	
	number = ft_itoa(cmd->nb);
	if (!number)
		ft_error(data, "Error: malloc\n", -1);
	name = ft_strjoin(".here_doc", number);
	if (!name)
		ft_error(data, "Error: malloc\n", -1);
	ft_free_me(number);
	return (name);
}

void	ft_mhere_doc(t_mdata *data, t_command *cmd, t_files *file)
{
	char	*line;
	char	*name;
	
	name = get_hdoc_name(data, cmd);
	ft_meof(file);
	file->fd = open(name,
			O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file->fd < 0)
	{
		unlink(name);
		return (ft_error(data, "Error, here_doc\n", 1));
	}
	signal(SIGINT, &handle_siginthere);
	while (1)
	{
		line = readline("> ");
		if (is_eof(line, file) == 1)
			break ;
		write(file->fd, line, ft_strlen(line));
		write(file->fd, "\n", 1);
		free(line);
	}
	if (g_retval == 130)
	{
		handle_signals();
		close(file->fd);
		file->fd = open(name, O_RDONLY);
		return ;
	}
	free(line);
	close(file->fd);
	file->fd = open(name, O_RDONLY);
	printf("On open en O_RDONLY :%s=%i:\n", name, file->fd);
	ft_free_me(name);
	handle_signals();
	return (0);
}
