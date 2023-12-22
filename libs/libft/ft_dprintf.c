/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blai <blai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 23:59:47 by nuferron          #+#    #+#             */
/*   Updated: 2023/12/22 04:11:44 by blai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_specifier(char c)
{
	if (c == '%')
		return (1);
	if (c == 'c')
		return (1);
	if (c == 's')
		return (1);
	if (c == 'd' || c == 'i')
		return (1);
	if (c == 'p')
		return (1);
	if (c == 'u')
		return (1);
	if (c == 'x')
		return (1);
	if (c == 'X')
		return (1);
	return (0);
}

int	eval_flags(char *format, int i, t_flags *flags)
{
	default_flags(flags);
	if (format[i - 1] == '%' && ((format[i] >= 'a' && format[i] <= 'z')
			|| format[i] == 'X' || format[i] == '%'))
		return (i);
	else
		i = capturing_flags(format, i, flags);
	while (!is_specifier(format[i]))
		i++;
	return (i);
}

static int	format_specifier(int fd, char c, va_list args, t_flags *flags)
{
	if (c == '%')
		return (percentage_bonus(fd, flags));
	else if (c == 'c')
		return (char_bonus(fd, va_arg(args, int), flags));
	else if (c == 's')
		return (string_bonus(fd, va_arg(args, char *), flags));
	else if (c == 'd' || c == 'i')
		return (num_bonus(fd, va_arg(args, int), flags));
	else if (c == 'p')
		return (pointer_bonus(fd, va_arg(args, unsigned long long), flags));
	else if (c == 'u')
		return (unsigned_bonus(fd, va_arg(args, unsigned int), flags));
	else if (c == 'x')
		return (hex_min_bonus(fd, va_arg(args, unsigned int), flags));
	else if (c == 'X')
		return (hex_cap_bonus(fd, va_arg(args, unsigned int), flags));
	return (0);
}

int	lets_print(int fd, va_list args, char const *format)
{
	t_flags	flags;
	int		i;
	int		nbytes;
	int		aux;

	i = 0;
	nbytes = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			i = eval_flags((char *)format, i, &flags);
			aux = format_specifier(fd, format[i], args, &flags);
		}
		else
			aux = write(fd, &format[i], 1);
		nbytes += aux;
		if (aux == -1)
			return (-1);
		i++;
	}
	return (nbytes);
}

int	ft_dprintf(int fd, char const *format, ...)
{
	va_list	arg_ptr;
	int		nbytes;

	va_start(arg_ptr, format);
	nbytes = lets_print(fd, arg_ptr, format);
	va_end(arg_ptr);
	return (nbytes);
}
