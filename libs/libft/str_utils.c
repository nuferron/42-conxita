/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:59:02 by blvilarn          #+#    #+#             */
/*   Updated: 2023/05/22 15:42:02 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c, int *i, int *len)
{
	(*i)++;
	(*len)++;
	return (write(1, &c, 1));
}

int	ft_putstr(char *s, int *i, int *len)
{
	int	j;

	(*i)++;
	if (!s)
	{
		(*len) += 6;
		return (write(1, "(null)", 6));
	}
	j = 0;
	while (s[j] != '\0')
	{
		if (write(1, &s[j], sizeof(char)) != 1)
			return (-1);
		i++;
		(*len)++;
		j++;
	}
	return (0);
}
