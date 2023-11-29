/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:01:21 by nuferron          #+#    #+#             */
/*   Updated: 2023/11/29 16:30:18 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int	format_distributor(int fd, char c, va_list args)
{
	if (c == '%')
		return (write(fd, "%", 1));
	if (c == 'c')
		return (print_char(fd, va_arg(args, int)));
	if (c == 's')
		return (print_string(fd, va_arg(args, char *)));
	if (c == 'd' || c == 'i')
		return (print_num(fd, va_arg(args, int)));
	if (c == 'p')
		return (print_pointer(fd, va_arg(args, unsigned long long)));
	if (c == 'u')
		return (print_unsigned_num(fd, va_arg(args, unsigned int)));
	if (c == 'x')
		return (print_hex_min(fd, va_arg(args, unsigned int)));
	if (c == 'X')
		return (print_hex_cap(fd, va_arg(args, unsigned int)));
	return (0);
}

int	ft_dprintf(int fd, char const *format, ...)
{
	va_list	arg_ptr;
	int		i;
	int		wr_len;
	int		aux;

	i = 0;
	wr_len = 0;
	va_start(arg_ptr, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			aux = format_distributor(fd, format[i], arg_ptr);
		}
		else
			aux = write(fd, &format[i], 1);
		wr_len += aux;
		if (aux == -1)
			return (-1);
		i++;
	}
	va_end(arg_ptr);
	return (wr_len);
}
