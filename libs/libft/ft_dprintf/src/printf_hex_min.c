/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_hex_min.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:04:11 by nuferron          #+#    #+#             */
/*   Updated: 2023/11/29 15:56:11 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int	hex_conversion_min(int fd, unsigned int dec_num)
{
	static char	*hex_base_min = "0123456789abcdef";
	int			nbytes;
	int			hex_value;
	int			w_protection;

	hex_value = hex_base_min[dec_num % 16];
	nbytes = 0;
	if (dec_num / 16 > 0)
	{
		dec_num = dec_num / 16;
		w_protection = hex_conversion_min(fd, dec_num);
		if (w_protection == -1)
			return (-1);
		nbytes += w_protection;
	}
	if (write(fd, &hex_value, 1) == -1)
		return (-1);
	nbytes++;
	return (nbytes);
}

int	print_hex_min(int fd, unsigned int dec_num)
{
	if (dec_num == 0)
		return (write(fd, "0", 1));
	return (hex_conversion_min(fd, dec_num));
}
