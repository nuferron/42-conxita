/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:17:27 by nuferron          #+#    #+#             */
/*   Updated: 2023/11/29 15:17:44 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int	print_string(int fd, char *str)
{
	int	nbytes;
	int	w_protection;

	nbytes = 0;
	if (!str)
		return (write(fd, "(null)", 6));
	while (str[nbytes] != '\0')
	{
		w_protection = write(fd, &str[nbytes], 1);
		nbytes++;
		if (w_protection == -1)
			return (-1);
	}
	return (nbytes);
}
