/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:27:52 by afontain          #+#    #+#             */
/*   Updated: 2024/02/22 16:05:36 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_export_value(char *var)
{
	int	i;

	i = nb_char_equal(var);
	if (var[i] == '=' && var[i + 1] != '\0')
		return (1);
	return (-1);
}
