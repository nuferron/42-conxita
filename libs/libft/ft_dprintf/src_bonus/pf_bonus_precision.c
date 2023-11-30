/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bonus_precision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:02:41 by nuferron          #+#    #+#             */
/*   Updated: 2023/09/13 21:23:58 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int	precision_len(char type, int len, t_flags *flags)
{
	int	len_to_print;

	if (type == 's')
	{
		if (flags->prec_width >= len)
			len_to_print = len;
		else
			len_to_print = flags->prec_width;
	}
	if (type == 'd' )
	{
		if (flags->prec_width >= len)
			len_to_print = flags->prec_width;
		else
			len_to_print = len;
	}
	return (len_to_print);
}

int	precision_padding(char	*str, int len, int len_precision)
{
	int	i;

	i = 0;
	while (len_precision > len)
	{
		str[i] = '0';
		i++;
		len_precision--;
	}
	return (i);
}
