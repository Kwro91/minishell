/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:14:10 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 19:53:08 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_string(char *str)
{
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
				ft_error(data, "Error: malloc\n", -1);
		}
	}
	else
		cmd->line = ft_strdup("");
	ft_free_me(start);
	ft_free_me(end);
}

char	*change_letter2(t_command *cmd, char *value, char *start, char *end)
{		
	char *tmp;
	
	tmp = ft_strjoin(start, value);
	if (is_string(end) == 1)
	{	
		cmd->line = ft_strjoin(tmp, end);
		ft_free_me(tmp);
	}
	else
		cmd->line = tmp;
	return (cmd->line);
}

void	change_letter(t_mdata *data, t_command *cmd, int i, char *value, int len)
{
	// char	*tmp;
	char	*start;
	char	*end;

	start = ft_strdupuntil(data, cmd->line, i);
	end = ft_strdup(&cmd->line[i + len + 1]);
	ft_free_me(cmd->line);
	if (is_string(start) == 1)
	{
		cmd->line = change_letter2(cmd, value, start, end);
		// tmp = ft_strjoin(start, value);
		// if (is_string(end) == 1)
		// {	
		// 	cmd->line = ft_strjoin(tmp, end);
		// 	ft_free_me(tmp);
		// }
		// else
		// 	cmd->line = tmp;
	}
	else
	{
		if (is_string(end) == 1)
			cmd->line = ft_strjoin(value, end);
		else
			cmd->line = ft_strdup(value);
	}
	ft_free_me(start);
	ft_free_me(end);
	if (!cmd->line)
		ft_error(data, "Error: malloc\n", -1);
}
