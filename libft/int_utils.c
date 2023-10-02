/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:29:19 by blvilarn          #+#    #+#             */
/*   Updated: 2023/05/22 15:42:08 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(long long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_putnbr(long long n, int *i, int *len)
{
	char	buffer[12];
	int		j;

	j = get_len(n);
	(*i)++;
	buffer[j] = '\0';
	if (n == 0)
	{
		(*len)++;
		return (write(1, "0", 1));
	}
	if (n < 0)
	{
		buffer[0] = '-';
		n *= -1;
	}
	while (n)
	{
		buffer[--j] = (n % 10) + '0';
		n /= 10;
	}
	return (ft_putstr(buffer, &j, len));
}

static int	get_len_base(unsigned long n, int base)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}

int	putn_b(char *base_str, unsigned long n, int *i, int *len)
{
	char	buffer[17];
	int		base;
	int		j;

	base = ft_strlen(base_str);
	j = get_len_base(n, base);
	(*i)++;
	buffer[j] = '\0';
	if (n == 0)
	{
		(*len)++;
		return (write(1, "0", 1));
	}
	while (n)
	{
		buffer[--j] = base_str[n % base];
		n /= base;
	}
	return (ft_putstr(buffer, &j, len));
}
