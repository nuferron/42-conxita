/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:33:29 by blvilarn          #+#    #+#             */
/*   Updated: 2023/05/22 15:35:46 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_content(const char *str, va_list ptr, int *i, int *len)
{
	if (str[*i] == 'c')
		return (ft_putchar(va_arg(ptr, int), i, len));
	if (str[*i] == 's')
		return (ft_putstr(va_arg(ptr, char *), i, len));
	if (str[*i] == 'p')
	{
		if (write(1, "0x", 2) != 2)
			return (-1);
		(*len) += 2;
		return (putn_b("0123456789abcdef", va_arg(ptr, unsigned long), i, len));
	}
	if (str[*i] == 'd' || str[*i] == 'i')
		return (ft_putnbr(va_arg(ptr, int), i, len));
	if (str[*i] == 'u')
		return (ft_putnbr(va_arg(ptr, unsigned int), i, len));
	if (str[*i] == 'x')
		return (putn_b("0123456789abcdef", va_arg(ptr, unsigned int), i, len));
	if (str[*i] == 'X')
		return (putn_b("0123456789ABCDEF", va_arg(ptr, unsigned int), i, len));
	if (str[*i] == '%')
		return (ft_putchar('%', i, len));
	else
		return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	int		i;
	int		len;

	va_start(ptr, str);
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '%')
		{
			if (write(1, &str[i], 1) != 1)
				return (-1);
			len++;
			i++;
		}
		else
		{
			i++;
			if (print_content(str, ptr, &i, &len) == -1)
				return (-1);
		}
	}
	return (len);
}
