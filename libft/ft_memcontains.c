/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcontains.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:40:07 by blvilarn          #+#    #+#             */
/*   Updated: 2023/09/19 13:58:15 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcontains(void *mem, int x, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (((int *)mem)[i] == x)
			return (1);
		i++;
	}
	return (0);
}
