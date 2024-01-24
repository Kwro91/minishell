/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:38:43 by besalort          #+#    #+#             */
/*   Updated: 2024/01/24 17:12:45 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dup_word(char	*line, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * len + 1);
	while (i < len && line[i])
	{
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*next_word(char *line)
{
	int	i;
	int	count;
	int	apo;

	i = 0;
	apo = 0;
	count = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] == '"' && apo == 0)
		{
			apo = 1;
			i++;
		}
		if (line[i] == '"' && apo == 1)
			break ;
		if (apo == 0 && ft_isalnum(line[i]) == 0)
			break ;
		i++;
		count++;
	}
	if (count == 0)
		return (NULL);
	return (dup_word(&line[i - count], count));
}

// int	is_here_doc(t_mdata *data, char *line)
// {
// 	int		i;
// 	t_files	*tmp;

// 	i = 0;
// 	if (data->eof)
// 		free(data->eof);
// 	while (line[i + 1])
// 	{
// 		if (line[i] == '<' && line[i + 1] == '<')
// 		{
			
// 			return (next_word(&line[i + 2]));
// 		}
// 		i++;
// 	}
// 	return (0);
// }

char	*redir(t_mdata *data, t_command *cmd)
{
	// int	i;

	// i = 0;
	// data->eof = is_here_doc(data, line);
	// data->here_doc = 1;
	// if (!data->eof)
	// {
		data->here_doc = 0;
		// if (is_fd_in(data, line) == 1 && data->in.files)
		// 	printf("fd_in = %s\n", data->in.files);
	// }
	// if (data->here_doc == 1)
		// printf("EOF = %s\n", data->eof);
	// if (is_fd_out(data, line) == 1 && data->out.files)
	// 		printf("fd_out = %s\n", data->out.files);
	is_fd_in(data, cmd);
	// is_fd_out(data, line);
	ft_open_mfiles(data, cmd);
	return (redir_rewrite(data, cmd));
	// while (line[i])
	// {
	// 	break ;
	// }
	
}
