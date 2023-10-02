/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:31:34 by blvilarn          #+#    #+#             */
/*   Updated: 2023/09/05 11:47:40 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(const char *str)
{
	double	nb;
	double	part;
	double	sign;

	while (ft_iswhitespace(*str))
		str++;
	sign = 1.0;
	if (*str == '-')
		sign = -1.0;
	if (*str == '-' || *str == '+')
		str++;
	nb = 0.0;
	while (*str >= '0' && *str <= '9')
		nb = nb * 10 + (*(str++) - '0');
	if (*str == '.' || *str == ',')
	{
		while (*(++str) >= '0' && *str <= '9')
			part = 0.0;
		while (*(--str) >= '0' && *str <= '9')
			part = (part + (*str - '0')) / 10.0;
		nb += part;
	}
	return (nb * sign);
}
