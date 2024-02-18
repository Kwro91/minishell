/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:14:10 by besalort          #+#    #+#             */
/*   Updated: 2024/02/18 20:21:37 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_vdollar(t_mdata *data, t_command *cmd, int i, int len)
{
	char	*start;
	char	*end;

	start = ft_strdupuntil(data, cmd->line, i);
	end = ft_strdup(&cmd->line[i + len]);
	if (start)
	{
		ft_free_me(cmd->line);
		if (!end)
			cmd->line = start;
		else
		{
			cmd->line = ft_strjoin(start, end);
			if (!cmd->line)
				ft_error(data, "Error: malloc\n", 1);
		}
	}
	else
	{
		ft_free_me(cmd->line);
		cmd->line = "";
	}
}

int	is_string(char *str)
{
	if (str)
		if (str[0] && str[0] != '\000' && str[0] != '\0')
			return (1);
	return (-1);
}

void	change_letter(t_mdata *data, t_command *cmd, int i, char *value, int len)
{
	char	*tmp;
	char	*start;
	char	*end;

	start = ft_strdupuntil(data, cmd->line, i);
	end = ft_strdup(&cmd->line[i + len + 1]);
	ft_free_me(cmd->line);
	if (is_string(start) == 1)
	{
		tmp = ft_strjoin(start, value);
		if (is_string(end) == 1)
		{	
			cmd->line = ft_strjoin(tmp, end);
			ft_free_me(tmp);
		}
		else
		{
			cmd->line = tmp;
		}
	}
	else
	{
		if (is_string(end) == 1)
		{
			cmd->line = ft_strjoin(value, end);
		}
		else
			cmd->line = value;
	}
	ft_free_me(start);
	ft_free_me(end);
	if (!cmd->line)
		ft_error(data, "Error: malloc\n", 1);
}