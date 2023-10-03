/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:07:37 by blvilarn          #+#    #+#             */
/*   Updated: 2022/10/24 16:23:55 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	slen;

	i = 0;
	slen = ft_strlen(s);
	while (i <= slen)
	{
		if (s[slen - i] == ((char )c))
			return (((char *)&s[slen - i]));
		i++;
	}
	if ('\0' == ((char )c))
		return (((char *)&s[slen - i]));
	return (NULL);
}
