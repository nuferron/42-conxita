/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:52:50 by blvilarn          #+#    #+#             */
/*   Updated: 2023/01/10 17:20:15 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print(char n, int fd)
{
	write(fd, &n, 1);
}

static void	recursiva(int n, int fd)
{
	if (n >= 10)
		recursiva(n / 10, fd);
	print('0' + n % 10, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			print('-', fd);
			n = -n;
		}
		recursiva(n, fd);
	}
}
