/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bonus_sign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:03:03 by nuferron          #+#    #+#             */
/*   Updated: 2023/09/13 21:23:58 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	str_to_front(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1] != '\0')
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
}

void	sign_to_front(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+' || str[0] == ' ')
		return ;
	while (str[i] == '0')
		i++;
	str[0] = str[i];
	str[i] = '0';
}

static char	*is_negative(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '0')
		i++;
	if (str[i] == '-' && i != 0 && str[i - 1] == '0')
	{
		str[0] = '-';
		str[i] = '0';
	}
	return (str);
}

static char	*signed_string(char	*str, char *signed_str, t_flags *flags)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	if (flags->sign == '+')
		signed_str[0] = '+';
	else if (flags->sign == ' ')
		signed_str[0] = ' ';
	while (i < len)
	{
		i++;
		signed_str[i] = str[i - 1];
	}
	return (signed_str);
}

char	*add_sign(char *str, t_flags *flags)
{
	char	*signed_str;

	str = is_negative(str);
	if (str[0] == '-' || flags->sign == '-')
		return (str);
	signed_str = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	if (!signed_str)
	{
		free(str);
		return (NULL);
	}
	signed_str = signed_string(str, signed_str, flags);
	free(str);
	return (signed_str);
}
