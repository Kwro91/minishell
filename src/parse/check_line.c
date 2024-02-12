/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:12:09 by besalort          #+#    #+#             */
/*   Updated: 2024/02/12 17:16:17 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_line_pipe(t_mdata *data, t_command *cmd)
{
	t_command	*tmp;
	int			good;
	int			i;

	tmp = cmd;
	while (tmp)
	{
		good = 0;
		i = 0;
		while (tmp->line[i])
		{
			if (tmp->line[i] > 32 && tmp->line[i] <= 126)
				good = 1;
			i++;
		}
		if (good == 0)
		{
			ft_error(data, "minishell: ", 0);
			ft_error(data, "syntax error near token ", 0);
			return (ft_error(data, "'|'\n", 0), -1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	is_allowed(char c)
{
	char	*string;
	int		i;

	i = 0;
	string = (" \"'<>?|$.-/=~");
	while (string && string[i])
	{
		if (c == string[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_before(t_mdata *data, char *line)
{
	int	i;
	int	good;

	i = 0;
	good = 0;
	while (line[i])
	{
		if (line[i] > 32 && line[i] <= 126)
			good = 1;
		if (ft_isalnum((int)line[i]) == 0 && is_allowed(line[i]) == 0)
		{
			ft_error(data, "Please don't use special character\n", 0);
			return (0);
		}
		i++;
	}
	return (good);
}
