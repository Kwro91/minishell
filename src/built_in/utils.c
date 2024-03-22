/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:15:35 by besalort          #+#    #+#             */
/*   Updated: 2024/03/22 17:47:40 by besalort         ###   ########.fr       */
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

int	ft_isword(int c)
{
	if (ft_isalnum(c) == 1 || c == 46 || c == 45 || c == 95)
		return (1);
	return (0);
}

char	*next_word(t_mdata *data, t_command *cmd, int i)
{
	int	count;
	int	apo;

	apo = 0;
	count = 0;
	while (i < (int)ft_strlen(cmd->line) && (ft_isword(cmd->line[i]) == 0 && cmd->line[i] != '$'))
		i++;
	while ((int)ft_strlen(cmd->line) > i && cmd->line[i])
	{
		if (cmd->line[i] == '$')
			return (find_var(data, cmd, i));
		if (cmd->line[i] == '"' && apo == 0)
			apo = 1;
		if ((cmd->line[i] == '"' && apo == 1)
			|| (apo == 0 && ft_isword(cmd->line[i]) == 0))
			break ;
		i++;
		count++;
	}
	if (count == 0)
		return (NULL);
	return (dup_word(data, cmd, count, (i - count)));
}
