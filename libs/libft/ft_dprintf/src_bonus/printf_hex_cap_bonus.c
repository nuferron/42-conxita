/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_hex_cap_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:03:48 by nuferron          #+#    #+#             */
/*   Updated: 2023/11/29 15:27:13 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int	hex_conversion_cap_bonus(unsigned int num)
{
	static char	*hex_base_cap = "0123456789ABCDEF";
	int			hex_value;

	hex_value = hex_base_cap[num % 16];
	return (hex_value);
}

static char	*hex_to_str_cap_bonus(unsigned int num, char *str)
{
	int		len;

	len = ft_strlen(str) + hex_len(num) - 1;
	while (num / 16 > 0)
	{
		str[len] = (char)hex_conversion_cap_bonus(num);
		num = num / 16;
		len--;
	}
	str[len] = (char)hex_conversion_cap_bonus(num);
	return (str);
}

char	*getting_hex_cap(unsigned int num, t_flags *flags)
{
	char	*str_precision;
	int		i;
	int		j;
	int		prec_len;

	j = 0;
	if (flags->hex == '#')
		flags->hex = 'X';
	i = hex_len(num);
	prec_len = precision_len('d', i, flags);
	str_precision = ft_calloc(prec_len + 1, sizeof(char));
	if (!str_precision)
		return (NULL);
	i = precision_padding(str_precision, i, prec_len);
	str_precision = hex_to_str_cap_bonus(num, str_precision);
	return (str_precision);
}

static char	*hex_cap_aux(unsigned int num, t_flags *flags)
{
	char	*str;
	char	*ptr;
	char	*final_str;

	if (num == 0)
		flags->hex = '$';
	if (flags->precision == '.' && flags->prec_width == 0 && num == 0)
		str = ft_strdup("");
	else
		str = getting_hex_cap(num, flags);
	if (!str)
		return (NULL);
	ptr = add_ox(str, flags);
	if (!ptr)
	{
		free(str);
		return (NULL);
	}
	final_str = add_padding(ptr, flags);
	free(str);
	if (flags->hex != '$')
		free(ptr);
	return (final_str);
}

int	hex_cap_bonus(int fd, unsigned int num, t_flags *flags)
{
	char	*final_str;
	char	*ptr;
	int		nbytes;

	ptr = hex_cap_aux(num, flags);
	if (!ptr)
		return (-1);
	final_str = add_padding(ptr, flags);
	free(ptr);
	if (!final_str)
		return (-1);
	ox_to_front(final_str, flags);
	nbytes = write(fd, final_str, ft_strlen(final_str));
	free(final_str);
	if (nbytes == -1)
		return (-1);
	return (nbytes);
}
