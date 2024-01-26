/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:10:52 by besalort          #+#    #+#             */
/*   Updated: 2024/01/22 17:59:34 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_retval;

int	main(int ac, char **av, char **env)
{
	g_retval = 0;
	t_mdata data;
	if (ac == 1)
	{
		init_built_int(&data);
		handle_signals();
		prompt(&data, ac, av, env);
	}
	else
		ft_printf("No args needed for minishell, please use : ./minishell\n");
    return (0);
}
