/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_char_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:03:17 by nuferron          #+#    #+#             */
/*   Updated: 2023/11/29 15:32:32 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	char_add_padding(char *str, t_flags *flags)
{
	int	i;

	i = 0;
	if (flags->padd_type == '0')
	{
		while (flags->width > 1)
		{
			str[i++] = '0';
			flags->width--;
		}
	}
	else
	{
		while (flags->width > 1)
		{
			str[i++] = ' ';
			flags->width--;
		}
	}
}

char	*char_padding(t_flags *flags)
{
	char	*char_padd;
	int		final_len;

	if (flags->width > 1)
		final_len = flags->width;
	else
		final_len = 1;
	char_padd = (char *)ft_calloc(final_len + 1, sizeof(char));
	if (!char_padd)
		return (NULL);
	char_add_padding(char_padd, flags);
	return (char_padd);
}

int	print_char_bonus(int fd, char *final_str, int c, t_flags *flags)
{
	int	nbytes;

	nbytes = 0;
	if (flags->padd_type == ' ' || flags->padd_type == '0')
	{
		nbytes = write(fd, final_str, ft_strlen(final_str));
		if (nbytes == -1)
			return (-1);
		nbytes += write(fd, &c, 1);
	}
	else if (flags->padd_type == '-')
	{
		nbytes = write(fd, &c, 1);
		if (nbytes == -1)
			return (-1);
		nbytes += write(fd, final_str, ft_strlen(final_str));
	}
	if (nbytes < ((int)ft_strlen(final_str) + 1))
		return (-1);
	return (nbytes);
}

int	char_bonus(int fd, int c, t_flags *flags)
{
	char	*final_str;
	int		nbytes;

	final_str = char_padding(flags);
	if (!final_str)
		return (-1);
	nbytes = print_char_bonus(fd, final_str, c, flags);
	free(final_str);
	return (nbytes);
}
