/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:17:43 by blvilarn          #+#    #+#             */
/*   Updated: 2023/09/22 17:10:52 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long	num;
	long	zrs;
	long	i;

	num = 0;
	zrs = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-')
	{
		zrs = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	num *= zrs;
	return (num);
}
