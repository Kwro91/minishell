/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:10:52 by besalort          #+#    #+#             */
/*   Updated: 2023/11/27 22:36:47 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	if (ac == 1)
	{
		handle_signals();
		prompt(ac, av, env);
	}
	else
		ft_printf("No args needed for minishell, please use : ./minishell\n");
    return (0);
}
