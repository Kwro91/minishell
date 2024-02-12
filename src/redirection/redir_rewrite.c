/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_rewrite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:15:57 by besalort          #+#    #+#             */
/*   Updated: 2024/02/12 17:39:07 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(t_mdata *data, char	*str, int len)
{
	char	*new;
	int		i;

	if (!str || len <= 0 || (int)ft_strlen(str) < len)
		return (NULL);
	i = 0;
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		ft_error(data, "Error: malloc\n", 1);
	while (str[i] && i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*sub_files_utils(t_mdata *data, t_command *cmd, t_files *tmp, char c)
{
	int		i;
	char	*new;
	char	*one;
	char	*two;

	i = 0;
	one = NULL;
	two = NULL;
	while (cmd->line[i])
	{
		if (one == NULL && cmd->line[i] == c)
			one = ft_strndup(data, cmd->line, i);
		else if (one != NULL && ft_strncmp(&cmd->line[i], tmp->files,
				ft_strlen(tmp->files)) == 0)
		{
			two = ft_strdup(&cmd->line[i + ft_strlen(tmp->files)]);
			break ;
		}
		i++;
	}
	new = ft_strjoin(one, two);
	if (!new)
		ft_error(data, "Error: malloc\n", 1);
	return (new);
}

void	sub_files(t_mdata *data, t_command *cmd)
{
	t_files	*tmp;

	tmp = NULL;
	tmp = cmd->in;
	while (tmp)
	{
		if (cmd->in)
			cmd->line = sub_files_utils(data, cmd, tmp, '<');
		tmp = tmp->next;
	}
	tmp = cmd->out;
	while (tmp)
	{
		if (cmd->out)
			cmd->line = sub_files_utils(data, cmd, tmp, '>');
		tmp = tmp->next;
	}
}
