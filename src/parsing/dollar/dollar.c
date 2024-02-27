/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:52:09 by afontain          #+#    #+#             */
/*   Updated: 2024/02/20 20:02:15 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdupfromuntil(t_mdata *data, char *src, int i, int n)
{
	char	*dest;
	char	*tmp;
	int		j;

	j = 0;
	if (n < 0)
		return (NULL);
	if (!src || ((int)ft_strlen(src) < i))
		return (NULL);
	tmp = next_word(data, &src[i]);
	dest = malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	ft_free_me(tmp);
	if (!dest)
		return (ft_error(data, "Error malloc\n", -1), NULL);
	while (src[i] && n > 0)
	{
		dest[j++] = src[i++];
		n--;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_strdupuntil(t_mdata *data, char *src, int i)
{
	char	*dest;
	int		j;

	j = 0;
	if (!src)
		return (NULL);
	dest = malloc (sizeof(char) * i + 1);
	if (!dest)
		return (ft_error(data, "Error malloc\n", -1), NULL);
	while (src[j] && j < i)
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

int	handle_dollar2(t_mdata *data, t_command *cmd, int i)
{
	int	k;

	k = 0;
	if (ft_isalpha(cmd->line[i + 1]) == 1)
		return (handle_letter(data, cmd, i));
	else
		return (dollar_left(data, cmd, i));
	return (k);
}

int	handle_dollar(t_mdata *data, t_command *cmd, int i)
{
	int	k;

	k = 0;
	if (cmd->line[i + 1] == '?')
		return (replace_retval(data, cmd, i));
	else if (cmd->line[i + 1] == '\'' || cmd->line[i + 1] == '"')
	{	
		cmd->line = del_qdollar(data, cmd, i);
		k = ft_strlen(del_qdollar(data, cmd, i));
	}
	else
		i = handle_dollar2(data, cmd, i);
	return (i + k);
}
