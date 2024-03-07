/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:31:41 by besalort          #+#    #+#             */
/*   Updated: 2024/03/07 17:10:26 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_error(t_mdata *data, char **arg)
{
	ft_error(data, "minishell: exit: ", 2);
	ft_error(data, arg[0], 2);
	ft_error(data, ": numeric argument required\n", 2);
}

int	ft_count_arg(t_mdata *data, char **arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
		i++;
	if (i > 1 && ft_isdigit(arg[0][0]) == 1)
		printf("minishell: exit: too many arguments\n");
	else if (ft_isalpha(arg[0][0])== 1)
		exit_error(data, arg);
	return (i);
}

void	exit_mini(t_mdata *data, char **arg)
{
	if (arg == NULL || arg[1] == NULL || ft_count_arg(data, &arg[1]) != 1)
	{
		if (arg && arg[1] && ft_isdigit(arg[1][0]) == 1)
		{
			g_retval = 1;
			return ;
		}
		else 
		{
			ft_free_mini(data);
			exit(g_retval);
		}
	}
	else
	{
		if (ft_isalpha(arg[1][0])== 1)
			g_retval = 2;
		else
		{
			g_retval = ft_atoi(arg[1]);
			ft_free_mini(data);
			exit(g_retval);
		}
	}
}