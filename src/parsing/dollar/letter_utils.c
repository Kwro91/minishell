/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:14:10 by besalort          #+#    #+#             */
/*   Updated: 2024/02/19 15:02:50 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_string(char *str)
{
	// int i = str[0];
	// printf("str[0]=:%i:\n", i);
	if (str)
		if (str[0] && str[0] != 0 && str[0] != '\0')
			return (1);
	return (-1);
}

void	del_vdollar(t_mdata *data, t_command *cmd, int i, int len)
{
	char	*start;
	char	*end;

	start = ft_strdupuntil(data, cmd->line, i);
	end = ft_strdup(&cmd->line[i + len + 1]);
	ft_free_me(cmd->line);
	if (is_string(start) == 1)
	{
		if (is_string(end) == 0)
			cmd->line = start;
		else
		{
			cmd->line = ft_strjoin(start, end);
			if (!cmd->line)
				ft_error(data, "Error: malloc\n", 1);
		}
	}
	else
		cmd->line = ft_strdup("");
	ft_free_me(start);
	ft_free_me(end);
}

void	change_letter(t_mdata *data, t_command *cmd, int i, char *value, int len)
{
	char	*tmp;
	char	*start;
	char	*end;

	start = ft_strdupuntil(data, cmd->line, i);
	end = ft_strdup(&cmd->line[i + len + 1]);
	ft_free_me(cmd->line);
	if (is_string(start) == 1) //start
	{
		tmp = ft_strjoin(start, value);
		if (is_string(end) == 1) //end && start
		{	
			cmd->line = ft_strjoin(tmp, end);
			ft_free_me(tmp);
		}
		else //!end && start
		{
			cmd->line = tmp;
		}
	}
	else //!start
	{
		if (is_string(end) == 1) //end && !start
		{
			cmd->line = ft_strjoin(value, end);
		}
		else //!end && !start
			cmd->line = ft_strdup(value);
	}
	ft_free_me(start);
	ft_free_me(end);
	if (!cmd->line)
		ft_error(data, "Error: malloc\n", 1);
}