/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_rewrite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:15:57 by besalort          #+#    #+#             */
/*   Updated: 2024/03/22 14:07:18 by afontain         ###   ########.fr       */
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
		ft_error(data, "Error: malloc\n", -1);
	while (str[i] && i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
