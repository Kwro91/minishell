/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:50:59 by besalort          #+#    #+#             */
/*   Updated: 2024/03/21 17:32:38 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_me(char *str)
{
	if (str)
		free(str);
}

int	ft_close_me(int fd)
{
	if (fd > -1)
	{
		close (fd);
		return (-1);
	}
	return (fd);
}
