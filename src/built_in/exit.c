/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:31:41 by besalort          #+#    #+#             */
/*   Updated: 2024/02/22 16:07:23 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_arg(t_mdata *data, char	**arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
		i++;
	if (i > 1)
		ft_error(data, "minishell: exit: too many arguments\n", 1);
	return (i);
}

void	exit_mini(t_mdata *data, char **arg)
{
	int	value;

	if (arg == NULL || ft_count_arg(data, &arg[1]) != 1)
	{
		ft_free_mini(data);
		exit(g_retval);
	}
	value = ft_atoi(arg[1]);
	ft_free_mini(data);
	exit(value);
}
