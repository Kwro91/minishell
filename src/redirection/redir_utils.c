/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:54:38 by besalort          #+#    #+#             */
/*   Updated: 2024/01/15 16:50:36 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_count(t_mdata *data, int count)
{
	if (data->here_doc == 1)
	{
		count += 2;
		count += ft_strlen(data->eof);
	}
	if (data->in.file != NULL)
	{
		count++;
		count += ft_strlen(data->in.file);
	}
	if (data->out.file != NULL)
	{
		count++;
		count += ft_strlen(data->out.file);
	}
	printf("count = %i\n", count);
	return (count);
}

char	*redir_rewrite(t_mdata *data, char *line)
{
	int	count;

	count = 0;
	get_count(data, count);
	return (line);
}

int	is_fd_in(t_mdata *data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1])
		{
			data->in.file = next_word(&line[i + 1]);
			return (1);
		}
		i++;
	}
	return 0;
}

int	is_fd_out(t_mdata *data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' && line[i + 1])
		{
			data->out.file = next_word(&line[i + 1]);
			return (1);
		}
		i++;
	}
	return 0;
}