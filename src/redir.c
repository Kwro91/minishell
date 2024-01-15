/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:38:43 by besalort          #+#    #+#             */
/*   Updated: 2024/01/15 14:40:36 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_word(char	*line, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * len + 1);
	while (i < len)
	{
		word[i] = line[i];
		i++;
	}
	word[i] = NULL;
	return (word);
}

char	*next_word(char *line)
{
	int	i;
	int	count;
	int	apo;

	i = 0;
	apo = 0;
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
		i++;
		count++;
	}
	if (count == 0)
		return (NULL);
	return (dup_word(&line[i], count));
}

char	*is_here_doc(char *line)
{
	int	i;

	i = 0;
	while (line[i + 1])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			return (next_word(&line[i + 1]));
		}
		i++;
	}
	return (NULL);
}

void	redir(t_mdata *data, char *line)
{
	int	i;

	i = 0;
	while (i)
	{
		break ;
	}
}
