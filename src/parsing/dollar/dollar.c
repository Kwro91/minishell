/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:52:09 by afontain          #+#    #+#             */
/*   Updated: 2024/02/13 18:09:45 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

// char	*replace_dollar(t_mdata *data, char *cmd, int i)
// {
// 	char *new_cmd;
// 	char *tmp;
	
// 	while (cmd[i+1] >= 48 && cmd[i+1] <= 57)
// 	{
// 		i++;
// 		new_cmd = ft_strdupfrom(cmd, i);
// 		return (new_cmd);
// 	}
// 	if (cmd[i+1] == '"')
// 		return (cmd);
// 	else 
// 	{
// 		new_cmd = find_var(data, tmp);
// 	}
// }

int	handle_dollar(t_mdata *data, t_command *cmd, int i)
{
	// char	*res;

	(void) data;
	while (cmd->line[i])
	{
		if (cmd->line[i+1] == '?')
		{
			// return (replace_retval(cmd, i));
			// free(cmd);
		}
		else if (ft_isalpha(cmd->line[i+1] == 1))
		{
				// return (replace_dollar(data, cmd, i));
			// free(cmd);
		}
		else if (cmd->line[i+1] == '\'' || cmd->line[i+1] == '"')
		{
			// return ();// retire les quotes;
		}
		else
		{
			// return ();// return un truc vide;
		}
		i++;	// nb_dollar++;
	}
	return (i);
}
