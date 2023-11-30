/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_pointers_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:09:18 by nuferron          #+#    #+#             */
/*   Updated: 2023/11/29 15:28:55 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int	hex_conversion_pointers(unsigned long long num)
{
	static char	*hex_base = "0123456789abcdef";
	int			hex_value;

	hex_value = hex_base[num % 16];
	return (hex_value);
}

static char	*get_pointer_address(unsigned long long num, char *str)
{
	int		len;

	len = pointer_len(num);
	while (num / 16 > 0)
	{
		len--;
		str[len] = (char)hex_conversion_pointers(num);
		num = num / 16;
	}
	str[--len] = (char)hex_conversion_pointers(num);
	return (str);
}

static char	*getting_pointer(unsigned long long num, t_flags *flags)
{
	char	*str_precision;
	int		i;
	int		j;
	int		prec_len;

	j = 0;
	flags->hex = 'x';
	i = pointer_len(num);
	prec_len = precision_len('d', i, flags);
	str_precision = ft_calloc(prec_len + 1, sizeof(char));
	if (!str_precision)
		return (NULL);
	i = precision_padding(str_precision, i, prec_len);
	str_precision = get_pointer_address(num, str_precision);
	return (str_precision);
}

static char	*pointers_aux(unsigned long long num, t_flags *flags)
{
	char	*str;
	char	*ptr;
	char	*final_str;

	if (flags->precision == '.' && flags->prec_width == 0
		&& num == 0)
		str = ft_strdup("");
	else
		str = getting_pointer(num, flags);
	if (!str)
		return (NULL);
	ptr = add_ox(str, flags);
	free(str);
	if (!ptr)
		return (NULL);
	final_str = add_padding(ptr, flags);
	free (ptr);
	return (final_str);
}

int	pointer_bonus(int fd, unsigned long long num, t_flags *flags)
{
	char	*final_str;
	int		nbytes;
	int		i;

	i = 0;
	final_str = pointers_aux(num, flags);
	if (!final_str)
		return (-1);
	if (flags->padd_type == '0')
	{
		while (final_str[i] != 'x')
			i++;
		final_str[i] = '0';
		final_str[1] = 'x';
	}
	ox_to_front(final_str, flags);
	nbytes = write(fd, final_str, ft_strlen(final_str));
	free(final_str);
	if (nbytes == -1)
		return (-1);
	return (nbytes);
}
