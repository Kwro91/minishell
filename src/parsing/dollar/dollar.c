/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:52:09 by afontain          #+#    #+#             */
/*   Updated: 2024/02/16 17:34:07 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdupfromuntil(t_mdata *data, char *src, int i, int n)
{
	char	*dest;

	if (n < 0)
		return (NULL);
	if (!src)
		return (NULL);
	dest = malloc (sizeof(char) * ft_strlen((const char *)src) - i - n + 1);
	if (!dest)
		return (ft_error(data, "Error malloc\n", 1), NULL);
	while (src[i] && n > 0)
	{
		dest[i] = src[i];
		i++;
		n--;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdupfrom(t_mdata *data, char *src, int i)
{
	char	*dest;

	if (!src)
		return (NULL);
	dest = malloc (sizeof(char) * ft_strlen((const char *)src) - i + 1);
	if (!dest)
		return (ft_error(data, "Error malloc\n", 1), NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdupuntil(t_mdata *data, char *src, int i)
{
	char	*dest;
	int j;
	
	j = 0;
	if (!src)
		return (NULL);
	dest = malloc (sizeof(char) * i + 1);
	if (!dest)
		return (ft_error(data, "Error malloc\n", 1), NULL);
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
	
	k = 0;
	if (ft_isalpha(cmd->line[i+1]) == 1)
		return (handle_letter(data, cmd, i));
	else
		return(dollar_left(data, cmd, i));
	return (k);
}

int	handle_dollar(t_mdata *data, t_command *cmd, int i)
{
	int k;
	// char	*new;

	k = 0;
	if (cmd->line[i+1] == '?')
		return(replace_retval(data, cmd, i));
	else if (cmd->line[i+1] == '\'' || cmd->line[i+1] == '"')
	{	
		cmd->line = suppr_dollar(data, cmd, i);
		// free(cmd->line);
		// cmd->line = new;
		k = ft_strlen(suppr_dollar(data, cmd, i));
	}
	else
	{
		printf("qhqhh\n");
		handle_dollar2(data, cmd, i);
	}
	return(i + k);
}
