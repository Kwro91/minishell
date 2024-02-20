/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_rewrite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:15:57 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 16:18:39 by afontain         ###   ########.fr       */
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
	while (cmd->line[i++])
	{
		if (one == NULL && cmd->line[i] == c)
			one = ft_strndup(data, cmd->line, i);
		else if (one != NULL && ft_strncmp(&cmd->line[i], tmp->files,
				ft_strlen(tmp->files)) == 0)
		{
			two = ft_strdup(&cmd->line[i + ft_strlen(tmp->files)]);
			break ;
		}
	}
	new = ft_strjoin(one, two);
	ft_free_me(one);
	ft_free_me(two);
	if (!new)
		ft_error(data, "Error: malloc111\n", 1);
	return (new);
}

void	sub_files(t_mdata *data, t_command *cmd)
{
	t_files	*tmp;
	char	*new;

	tmp = cmd->in;
	while (tmp)
	{
		if (tmp)
		{
			new = sub_files_utils(data, cmd, tmp, '<');
			ft_free_me(cmd->line);
			cmd->line = new;
		}
		tmp = tmp->next;
	}
	tmp = cmd->out;
	while (tmp)
	{
		if (tmp)
		{
			new = sub_files_utils(data, cmd, tmp, '>');
			ft_free_me(cmd->line);
			cmd->line = new;
		}
		tmp = tmp->next;
	}
}
