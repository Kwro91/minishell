/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:10:52 by besalort          #+#    #+#             */
/*   Updated: 2024/01/11 17:51:44 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_mdata data;
	if (ac == 1)
	{
		init_built_int(&data);
		handle_signals();
		prompt(&data, ac, av, env);
	}
	// if (ac >= 5)
	// 	ft_pipex(ac -1, &av[1], env);
	else
		ft_printf("No args needed for minishell, please use : ./minishell\n");
    return (0);
}
