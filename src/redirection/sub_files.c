/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:25:43 by besalort          #+#    #+#             */
/*   Updated: 2024/03/26 15:22:41 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_string(t_mdata *data, t_command *cmd, t_files *tmp, int *i)
{
	char	*one;
	char	*two;
	char	*new;

	new = NULL;
	while (cmd->line && cmd->line[*i])
	{
		if (ft_strncmp(&cmd->line[*i], tmp->files, get_file_len(tmp->files))
			== 0)
		{
			one = ft_strndup(data, cmd->line, *i);
			two = ft_strdup(&cmd->line[*i + get_file_len(tmp->files)]);
			if (!two || !one)
				return (ft_error(data, "Error: strdup\n", -1), NULL);
			new = ft_strjoin(one, two);
			if (!new)
				return (ft_error(data, "Error: strjoin\n", -1), NULL);
			ft_free_me(one);
			ft_free_me(two);
			return (new);
		}
		*i = *i + 1;
	}
	return (new);
}

char	*remove_c2(char *one, char *two, t_command *cmd, t_mdata *data)
{	
	char	*new;

	new = NULL;
	if (!one && two)
	{
		new = ft_strdup(two);
		if (!new)
			return (ft_error(data, "Error: strdup\n", -1), NULL);
		return (new);
	}
	if (two && one)
	{
		new = ft_strjoin(one, two);
		if (!new)
			return (ft_error(data, "Error: strjoin\n", -1), NULL);
	}
	if (!new)
		cmd->good = -1;
	return (new);
}

char	*remove_c(t_mdata *data, t_command *cmd, char c, int *i)
{
	char	*one;
	char	*two;
	char	*new;

	new = NULL;
	while (cmd->line && cmd->line[*i])
	{
		if (cmd->line[*i] == c)
		{
			one = ft_strndup(data, cmd->line, *i);
			if (cmd->line[*i + 1] == c)
				*i = *i + 1;
			if (!&cmd->line[*i + 1])
				return (one);
			two = ft_strdup(&cmd->line[*i + 1]);
			new = remove_c2(one, two, cmd, data);
			ft_free_me(one);
			ft_free_me(two);
			return (new);
		}
		*i = *i + 1;
	}
	return (new);
}

void	sub_files_utils(t_mdata *data, t_command *cmd, t_files *tmp, char c)
{
	int		i;
	char	*one;
	char	*two;

	i = 0;
	one = NULL;
	two = NULL;
	one = remove_c(data, cmd, c, &i);
	ft_free_me(cmd->line);
	cmd->line = one;
	if (one)
		two = remove_string(data, cmd, tmp, &i);
	ft_free_me(one);
	if (two)
		cmd->line = ft_strdup(two);
	else
		cmd->line = NULL;
	ft_free_me(two);
}

void	sub_files(t_mdata *data, t_command *cmd)
{
	t_files	*tmp;

	tmp = cmd->in;
	while (tmp)
	{
		if (tmp)
			sub_files_utils(data, cmd, tmp, '<');
		tmp = tmp->next;
	}
	tmp = cmd->out;
	while (tmp)
	{
		if (tmp)
		{
			sub_files_utils(data, cmd, tmp, '>');
		}
		tmp = tmp->next;
	}
}
