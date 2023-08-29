/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:49:29 by besalort          #+#    #+#             */
/*   Updated: 2022/11/28 15:04:58 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;
	t_list	*last;

	if (lst == NULL)
		return (0);
	i = 0;
	last = lst;
	while (last)
	{
		last = last->next;
		i++;
	}
	return (i);
}
