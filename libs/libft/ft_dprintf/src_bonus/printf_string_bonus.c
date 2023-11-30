/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_string_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:07:10 by nuferron          #+#    #+#             */
/*   Updated: 2023/11/29 15:29:16 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static char	*getting_string(char *str, t_flags *flags)
{
	char	*str_precision;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (flags->precision == '.')
		len = precision_len('s', (int)ft_strlen(str), flags);
	else
		len = (int)ft_strlen(str);
	str_precision = (char *) ft_calloc(len + 1, sizeof(char));
	if (!str_precision)
		return (NULL);
	while (i < len)
		str_precision[i++] = str[j++];
	return (str_precision);
}

static char	*string_null(char *str, t_flags *flags)
{
	int		free_protection;
	char	*ptr;

	free_protection = 0;
	if (!str)
	{
		str = ft_strdup("(null)");
		if (!str)
			return (NULL);
		free_protection = 1;
	}
	ptr = getting_string(str, flags);
	if (free_protection == 1)
		free(str);
	return (ptr);
}

int	string_bonus(int fd, char *str, t_flags *flags)
{
	char	*final_str;
	char	*ptr;
	int		nbytes;

	ptr = string_null(str, flags);
	if (!ptr)
		return (-1);
	final_str = add_padding(ptr, flags);
	free(ptr);
	if (!final_str)
		return (-1);
	nbytes = write(fd, final_str, ft_strlen(final_str));
	free(final_str);
	if (nbytes == -1)
		return (-1);
	return (nbytes);
}
