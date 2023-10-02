/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:33:31 by blvilarn          #+#    #+#             */
/*   Updated: 2022/10/25 19:27:25 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_absval(int num)
{
	if (num < 0)
		num = -num;
	return (num);
}

static int	get_len(int num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		++i;
	while (num)
	{
		num /= 10;
		++i;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*a;

	len = get_len(n);
	a = ft_calloc(len + 1, sizeof(char));
	if (!a)
		return (NULL);
	if (n == 0)
		a[0] = '0';
	if (n < 0)
		a[0] = '-';
	while (n)
	{
		len--;
		a[len] = ft_absval(n % 10) + '0';
		n /= 10;
	}
	return (a);
}
