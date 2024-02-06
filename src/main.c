/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:10:52 by besalort          #+#    #+#             */
/*   Updated: 2024/02/06 17:52:30 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_retval;

int	main(int ac, char **av, char **env)
{
	t_mdata	data;

	(void)av;
	g_retval = 0;
	if (ac == 1)
	{
		init_built_int(&data);
		handle_signals();
		prompt(&data, env);
	}
	else
		ft_printf("No args needed for minishell, please use : ./minishell\n");
	return (0);
}
