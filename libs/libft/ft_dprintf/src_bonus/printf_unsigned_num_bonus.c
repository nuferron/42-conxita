/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_unsigned_num_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:08:57 by nuferron          #+#    #+#             */
/*   Updated: 2023/11/29 15:29:42 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static char	*unsigned_itoa_conversion(unsigned int num, char *str)
{
	int	i;

	i = unsigned_len(num);
	if (num > 9)
		unsigned_itoa_conversion(num / 10, str);
	num = num % 10 + '0';
	str[i - 1] = num;
	return (str);
}

static char	*unsigned_itoa(unsigned int num)
{
	char	*str;
	int		nlen;

	nlen = unsigned_len(num);
	if (num == 0)
		return (ft_strdup("0"));
	str = (char *)malloc(sizeof(char) * (unsigned_len(num) + 1));
	if (!str)
		return (NULL);
	str[nlen] = '\0';
	unsigned_itoa_conversion(num, str);
	return (str);
}

static char	*getting_unsigned(unsigned int num, t_flags *flags)
{
	int		prec_len;
	int		i;
	int		j;
	char	*str_num;
	char	*str_precision;

	i = unsigned_len(num);
	j = 0;
	prec_len = precision_len('d', i, flags);
	str_precision = (char *)ft_calloc(prec_len + 1, sizeof(char));
	if (!str_precision)
		return (NULL);
	i = precision_padding(str_precision, i, prec_len);
	str_num = unsigned_itoa(num);
	if (!str_num)
	{
		free(str_precision);
		return (NULL);
	}
	while (str_num[j] != '\0')
		str_precision[i++] = str_num[j++];
	free(str_num);
	return (str_precision);
}

static void	unsigned_zero(char *str, t_flags *flags)
{
	int	i;

	i = 0;
	while (str[i] != '0')
		i++;
	if (flags->width == 0)
		str[i] = '\0';
	else
		str[i] = ' ';
}

int	unsigned_bonus(int fd, unsigned int num, t_flags *flags)
{
	char	*final_str;
	char	*str;
	int		nbytes;

	str = getting_unsigned(num, flags);
	if (!str)
		return (-1);
	final_str = add_padding(str, flags);
	free(str);
	if (!final_str)
		return (-1);
	if (num == 0 && flags->prec_width == 0
		&& flags->precision == '.' && flags->padd_type != '0' )
		unsigned_zero(final_str, flags);
	nbytes = write(fd, final_str, ft_strlen(final_str));
	free(final_str);
	if (nbytes == -1)
		return (-1);
	return (nbytes);
}
