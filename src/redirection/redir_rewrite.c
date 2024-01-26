/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_rewrite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:15:57 by besalort          #+#    #+#             */
/*   Updated: 2024/01/26 12:42:11 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_fileeeees(t_mdata *data, t_command *cmd)
{
	
}

int	count_file(t_files *files)
{
	t_files	*tmp;
	int		count;
	
	tmp = files;
	count = 0;
	while(tmp)
	{
		if (tmp->files)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	is_redir_and_file(t_mdata *data, t_command *cmd)
{
	int	i;
	int	j;
	t_command	*tmp;

	i = 0;
	j = 0;
	tmp = cmd;
	while(tmp->cmd[i])
	{
		while(cmd->cmd[i][j])
		{
			if (cmd->cmd[i][j] == '<' || cmd->cmd[i][j] == '>')
			j++;
		}
		i++;
	}
}

int	is_same_len(char *s1, char	*s2)
{
	int	one;
	int	two;

	one = ft_strlen(s1);
	two = ft_strlen(s2);
	if (one == two)
		return (one);
	return (0);
}

void	modif_cmd(t_mdata *data, t_command *cmd)
{
	t_command	*tmp;
	char		**new;
	int			i;
	int			len;

	i = 0;
	tmp = cmd;
	new = NULL;
	while(tmp->cmd[i])
	{
		len = is_same_len(tmp->cmd[i], tmp->in->files)
		if ()
	}
}
