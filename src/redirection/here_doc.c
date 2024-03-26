/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:06:24 by besalort          #+#    #+#             */
/*   Updated: 2024/03/26 15:38:25 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_eof(char	*line, t_files *file)
{
	int	len;

	len = ft_strlen(line);
	if (len == 0)
		return (1);
	if ((int)ft_strlen(file->files) != len)
		return (0);
	if (line && !ft_strlen(line))
		return (0);
	if (ft_strncmp(line, file->files, ft_strlen(file->files)) == 0)
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

void	ft_mhere_doc2(char *name, char *line, t_command *cmd, t_files *file)
{
	if (g_retval == 130)
	{
		cmd->good = -1;
		handle_signals();
		close(file->fd);
		file->fd = open(name, O_RDONLY);
		ft_free_me(name);
		return ;
	}
	free(line);
	close(file->fd);
	file->fd = open(name, O_RDONLY);
	ft_free_me(name);
	handle_signals();
}

void	ft_mhere_doc(t_mdata *data, t_command *cmd, t_files *file)
{
	char	*line;
	char	*name;

	if (cmd->good == -1)
		return ;
	name = get_hdoc_name(data, cmd);
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
	ft_mhere_doc2(name, line, cmd, file);
}
