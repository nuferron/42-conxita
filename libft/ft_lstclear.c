/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:47 by blvilarn          #+#    #+#             */
/*   Updated: 2022/10/31 19:40:44 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;

	if (lst)
	{
		while (*lst)
		{
			current = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = current;
		}
		lst = NULL;
	}
}
