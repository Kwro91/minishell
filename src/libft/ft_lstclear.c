/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:00:47 by besalort          #+#    #+#             */
/*   Updated: 2022/11/28 14:11:11 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*stock;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		stock = *lst;
		*lst = stock->next;
		ft_lstdelone(stock, del);
	}
	*lst = NULL;
}
