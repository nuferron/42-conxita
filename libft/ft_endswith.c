/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endswith.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:42:44 by blvilarn          #+#    #+#             */
/*   Updated: 2023/05/18 19:21:30 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_endswith(char *str, char *end)
{
	int	len_str;
	int	len_end;
	int	i;
	int	y;

	if (!str || !end)
		return (0);
	len_str = ft_strlen(str);
	len_end = ft_strlen(end);
	if (len_end > len_str)
		return (0);
	i = len_str - len_end;
	y = 0;
	while (str[i])
	{
		if (str[i++] != end[y++])
			return (0);
	}
	return (1);
}
