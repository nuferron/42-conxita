/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_num_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:05:56 by nuferron          #+#    #+#             */
/*   Updated: 2023/11/29 15:27:57 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int	num_len(int num)
{
	int	counter;

	counter = 1;
	while (num / 10 != 0)
	{
		num = num / 10;
		counter++;
	}
	return (counter);
}

static char	*aux_calloc(int len, int num)
{
	char	*str;

	str = NULL;
	if (num >= 0)
		str = (char *)ft_calloc(len + 1, sizeof(char));
	else if (num < 0)
		str = (char *)ft_calloc(len + 2, sizeof(char));
	return (str);
}

char	*putting_num_to_str(int num, t_flags *flags)
{
	int		j;
	int		prec_padd;
	int		prec_len;
	char	*str_precision;
	char	*str_num;

	j = 0;
	prec_len = precision_len('d', num_len(num), flags);
	str_precision = aux_calloc(prec_len, num);
	if (!str_precision)
		return (NULL);
	prec_padd = precision_padding(str_precision, num_len(num), prec_len);
	str_num = ft_itoa(num);
	if (!str_num)
	{
		free(str_precision);
		return (NULL);
	}
	while (str_num[j] != '\0')
		str_precision[prec_padd++] = str_num[j++];
	free(str_num);
	return (str_precision);
}

char	*getting_num(int num, t_flags *flags)
{
	char	*str_precision;

	if (num == 0
		&& (flags->precision == '.' && flags->prec_width == 0))
		str_precision = ft_strdup("");
	else
		str_precision = putting_num_to_str(num, flags);
	if (!str_precision)
		return (NULL);
	return (str_precision);
}

int	num_bonus(int fd, int num, t_flags *flags)
{
	char	*final_str;
	char	*str;
	int		nbytes;

	str = getting_num(num, flags);
	if (!str)
		return (-1);
	str = add_sign(str, flags);
	if (!str)
		return (-1);
	final_str = add_padding(str, flags);
	free(str);
	if (!final_str)
		return (-1);
	nbytes = write(fd, final_str, ft_strlen(final_str));
	free(final_str);
	if (nbytes == -1)
		return (-1);
	return (nbytes);
}
