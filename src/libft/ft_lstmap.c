/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:15:54 by besalort          #+#    #+#             */
/*   Updated: 2022/11/23 14:58:54 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*begin;

	begin = NULL;
	while (lst)
	{
		newlst = ft_lstnew((*f)(lst->content));
		if (!newlst)
		{
			ft_lstdelone(newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&begin, newlst);
		lst = lst->next;
	}
	return (begin);
}
