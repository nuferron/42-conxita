/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:08:26 by nuferron          #+#    #+#             */
/*   Updated: 2023/09/13 21:27:51 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int	unsigned_len(unsigned int num)
{
	int	counter;

	counter = 1;
	while (num / 10 != 0)
	{
		num = num / 10;
		counter++;
	}
	return (counter);
}

int	pointer_len(unsigned long long num)
{
	int	counter;

	counter = 1;
	while (num / 16 != 0)
	{
		num = num / 16;
		counter++;
	}
	return (counter);
}

int	hex_len(unsigned int num)
{
	int	counter;

	counter = 1;
	while (num / 16 != 0)
	{
		num = num / 16;
		counter++;
	}
	return (counter);
}
