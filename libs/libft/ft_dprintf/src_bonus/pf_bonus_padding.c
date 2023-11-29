/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bonus_padding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:02:27 by nuferron          #+#    #+#             */
/*   Updated: 2023/09/13 21:23:58 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	left_padding_zero(char *str, char *final_str, t_flags *flags)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (flags->width > len)
	{
		final_str[i++] = '0';
		flags->width--;
	}
	while (str[j] != '\0')
		final_str[i++] = str[j++];
	if (len > 1 && flags->padd_type == '0'
		&& (str[0] == '-' || str[0] == ' ' || str[0] == '+'))
		sign_to_front(final_str);
}

void	left_padding_sp(char *str, char *final_str, t_flags *flags)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (flags->width > len)
	{
		final_str[i++] = ' ';
		flags->width--;
	}
	while (str[j] != '\0')
		final_str[i++] = str[j++];
}

void	right_padding(char *str, char *final_str, t_flags *flags)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (str[j] != '\0')
		final_str[i++] = str[j++];
	while (flags->width > len)
	{
		final_str[i++] = ' ';
		flags->width--;
	}
}

char	*add_padding(char *str, t_flags *flags)
{
	char	*final_str;
	int		final_len;

	if ((int)ft_strlen(str) > flags->width)
		final_len = (int)ft_strlen(str);
	else
		final_len = flags->width;
	final_str = (char *)ft_calloc(final_len + 1, sizeof(char));
	if (!final_str)
		return (NULL);
	if (flags->padd_type == '0')
		left_padding_zero(str, final_str, flags);
	else if (flags->padd_type == ' ')
		left_padding_sp(str, final_str, flags);
	else
		right_padding(str, final_str, flags);
	return (final_str);
}
