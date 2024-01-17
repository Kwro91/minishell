/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:29:29 by besalort          #+#    #+#             */
/*   Updated: 2024/01/17 18:13:34 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**size_my_file(t_mdata *data, char *line, char c)
{
	int		i;
	int		count;
	char	**file;

	i = 0;
	count = 0;
	while (line[i + 1])
	{
		if (line[i] == c && line[i + 1] != c)
			count++;
		i++;
	}
	file = malloc(sizeof(char *) * count + 1);
	if (!file)
		ft_error(data, "Error : malloc\n", 1);
	return (file);
}

int	is_fd_out(t_mdata *data, char *line)
{
	int	i;
	int	j;
	int	value;

	i = 0;
	j = 0;
	value = 0;
	data->out.files = size_my_file(data, line, '>');
	while (line[i])
	{
		if (line[i] == '>' && line[i + 1])
		{
			data->out.files[j] = ft_strdup(next_word(&line[i + 1]));
			j++;
		}
		i++;
	}
	return (value);
}

int	is_fd_in(t_mdata *data, char *line)
{
	int	i;
	int	j;
	int	value;

	i = 0;
	j = 0;
	value = 0;
	data->in.files = size_my_file(data, line, '<');
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1])
		{
			data->in.files[j] = ft_strdup(next_word(&line[i + 1]));
			j++;
		}
		i++;
	}
	return (value);
}