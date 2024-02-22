/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:27:52 by afontain          #+#    #+#             */
/*   Updated: 2024/02/22 12:29:52 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_export_value(char *var)
{
	int	i;

	i = nb_char_equal(var);
	if (var[i + 1] == '=' && var[i + 2] != '\0')
		return (1);
	return (-1);
}
