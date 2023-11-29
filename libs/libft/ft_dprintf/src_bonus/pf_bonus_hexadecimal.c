/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bonus_hexadecimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:02:15 by nuferron          #+#    #+#             */
/*   Updated: 2023/09/13 21:23:58 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ox_to_front(char *str, t_flags *flags)
{
	int	i;

	i = 0;
	if (flags->padd_type == '0' && (flags->hex == 'X' || flags->hex == 'x'))
	{
		while ((str[i] != 'X' && str[i] != 'x') && str[i] != '\0')
			i++;
		if (i != 1)
		{
			str[1] = str[i];
			str[i] = '0';
		}
	}
}

char	*add_ox(char *str, t_flags *flags)
{
	int		len;
	char	*to_print;
	int		i;

	i = 2;
	len = ft_strlen(str);
	if (flags->hex == 'x' || flags->hex == 'X')
	{
		to_print = ft_calloc(len + 3, sizeof(char));
		if (!to_print)
			return (NULL);
		to_print[0] = '0';
		to_print[1] = 'x';
		if (flags->hex == 'X')
			to_print[1] = 'X';
		while (i < (len + 2))
		{
			to_print[i] = str[i - 2];
			i++;
		}
	}
	else
		to_print = str;
	return (to_print);
}
