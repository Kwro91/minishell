/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:52:09 by afontain          #+#    #+#             */
/*   Updated: 2024/02/15 17:42:04 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdupfromuntil(char *src, int i, int n)
{
	char	*dest;

	if (n < 0)
		return (NULL);
	if (!src)
		return (NULL);
	dest = malloc (sizeof(char) * ft_strlen((const char *)src) - i - n + 1);
	if (!dest)
		return (0);
	while (src[i] && n > 0)
	{
		dest[i] = src[i];
		i++;
		n--;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdupfrom(char *src, int i)
{
	char	*dest;

	if (!src)
		return (NULL);
	dest = malloc (sizeof(char) * ft_strlen((const char *)src) - i + 1);
	if (!dest)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdupuntil(char *src, int i)
{
	char	*dest;
	int j;
	
	j = 0;
	if (!src)
		return (NULL);
	dest = malloc (sizeof(char) * i + 1);
	if (!dest)
		return (0);
	while (src[j] && j < i)
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

int handle_dollar2(t_mdata *data, t_command *cmd, int i)
{
	int k;
	char	*new;
	
	(void) data;
	k = 0;
	if (ft_isalpha(cmd->line[i+1] == 1))
	{
		cmd->line = find_var(data, cmd);
		free(cmd->line);
		cmd->line = new;
		k = ft_strlen(find_var(data, cmd));
	}
	else
	{
		cmd->line = dollar_left(cmd->line, i);
		free(cmd->line);
		cmd->line = new;
		k = ft_strlen(dollar_left(cmd->line, i));
	}
	return (k);
}

int	handle_dollar(t_mdata *data, t_command *cmd, int i)
{
	int k;
	char	*new;

	(void) data;
	k = 0;
	if (cmd->line[i+1] == '?')
	{
		new = replace_retval(cmd->line, i);
		free(cmd->line);
		cmd->line = new;
		k = ft_strlen(replace_retval(cmd->line, i));
	}
	else if (cmd->line[i+1] == '\'' || cmd->line[i+1] == '"')
	{	
		cmd->line = suppr_dollar(cmd->line, i);
		free(cmd->line);
		cmd->line = new;
		k = ft_strlen(suppr_dollar(cmd->line, i));
	}
	else
		handle_dollar2(data, cmd, i);
	return(i + k);
}
