/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:15:35 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 18:22:38 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nb_word(char **text)
{
	int	i;

	i = 0;
	while (text && text[i])
		i++;
	return (i);
}

void	good_print(char	*line)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	if (!line)
		return ;
	while (line[i])
	{
		ft_printf("%c", line[i]);
		if (line[i] == '=' && equal == 0)
		{
			equal = 1;
			ft_printf("\"");
		}
		i++;
	}
	if (equal == 1)
		ft_printf("\"");
}

char	*next_word(t_mdata *data, char *line)
{
	int	i;
	int	count;
	int	apo;

	i = 0;
	apo = 0;
	count = 0;
	while (ft_strlen(line) > 0 && line[i] == ' ')
		i++;
	while ((int)ft_strlen(line) > i && line[i])
	{
		if (line[i] == '"' && apo == 0)
		{
			apo = 1;
			i++;
		}
		if ((line[i] == '"' && apo == 1)
			|| (apo == 0 && ft_isalnum(line[i]) == 0))
			break ;
		i++;
		count++;
	}
	if (count == 0)
		return (NULL);
	return (dup_word(data, &line[i - count], count));
}
