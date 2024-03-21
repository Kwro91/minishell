/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:25:43 by besalort          #+#    #+#             */
/*   Updated: 2024/03/21 18:32:59 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_file_len(char	*str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	if (str[i - 1] == '\n')
		i -= 1;
	return (i);
}

char	*remove_string(t_mdata *data, t_command *cmd, t_files *tmp, int *i)
{
	char	*one;
	char	*two;
	char	*new;


	new = NULL;
	while (cmd->line && cmd->line[*i])
	{
		if (ft_strncmp(&cmd->line[*i], tmp->files, get_file_len(tmp->files)) == 0)
		{
			one = ft_strndup(data, cmd->line, *i);
			// printf("dans string one:%s:\n", one);
			two = ft_strdup(&cmd->line[*i + get_file_len(tmp->files)]);
			// printf("dans string two:%s:\n", two);
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
			// printf("line:%s:\n", &cmd->line[*i + 1]);
			two = ft_strdup(&cmd->line[*i + 1]);
			if (!one && two)
				return (two);
			if (two && one)
			{
				new = ft_strjoin(one, two);
				// printf("oui !!!\n");
				if (!new)
					return (ft_error(data, "Error: strjoin\n", -1), NULL);
			}
			else
				cmd->good = -1;
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
	// printf("one :%s:\n", one);
	ft_free_me(cmd->line);
	cmd->line = one;
	// printf("avant two i=:%i:\n", i);
	if (one)
		two = remove_string(data, cmd, tmp, &i);
	// printf("two :%s:\n", two);
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
		{
			sub_files_utils(data, cmd, tmp, '<');
			// printf("cmd->line :%s:\n", cmd->line);
		}
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