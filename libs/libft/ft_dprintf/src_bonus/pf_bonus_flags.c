/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bonus_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:01:55 by nuferron          #+#    #+#             */
/*   Updated: 2023/09/13 21:23:58 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	default_flags(t_flags *flags)
{
	flags->padd_type = ' ';
	flags->sign = '-';
	flags->hex = '$';
	flags->width = 0;
	flags->precision = '*';
	flags->prec_width = 0;
}

int	capturing_flags_char(char *format, int i, t_flags *flags)
{
	while (format[i] == '0' || format[i] == '-'
		|| format[i] == '+' || format[i] == '#' || format[i] == ' ')
	{
		if (format[i] == '0' && flags->padd_type != '-')
			flags->padd_type = '0';
		else if (format[i] == '-')
			flags->padd_type = '-';
		else if (format[i] == ' ' && flags->sign != '+')
			flags->sign = ' ';
		else if (format[i] == '+')
			flags->sign = '+';
		else if (format[i] == '#')
			flags->hex = '#';
		i++;
	}
	return (i);
}

int	capturing_flags(char *format, int i, t_flags *flags)
{
	char	*ptr;

	if (is_specifier(format[i]) == 1)
		return (i);
	i = capturing_flags_char(format, i, flags);
	if (format[i] >= '0' && format[i] <= '9')
	{
		ptr = &format[i];
		flags->width = ft_atoi(ptr);
	}
	while (format[i] >= '0' && format[i] <= '9')
		i++;
	if (format[i] == '.')
	{
		flags->precision = '.';
		if (flags->padd_type == '0')
			flags->padd_type = ' ';
		i++;
		if (format[i] >= '0' && format[i] <= '9')
		{
			ptr = &format[i];
			flags->prec_width = ft_atoi(ptr);
		}
	}
	return (i);
}
