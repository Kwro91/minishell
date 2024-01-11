/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:40:12 by besalort          #+#    #+#             */
/*   Updated: 2024/01/11 17:03:32 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_command(char *command)
{
	char	*ptr;
	char	**commandp;

	ptr = ft_strchr(command, ' ');
	if (ptr != NULL)
		commandp = ft_split(command, ' ');
	else
	{
		commandp = ft_calloc(2, sizeof(char *));
		commandp[0] = ft_strdup(command);
		commandp[1] = NULL;
	}
	return (commandp);
}
