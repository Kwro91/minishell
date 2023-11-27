/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:14:31 by besalort          #+#    #+#             */
/*   Updated: 2023/11/27 16:19:09 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_built_int(t_mdata *data)
{
	data->env = NULL;
	data->export = NULL;
	data->paths = NULL;
	data->pwd = NULL;
}