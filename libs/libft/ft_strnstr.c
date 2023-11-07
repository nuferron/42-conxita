/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:41:30 by blvilarn          #+#    #+#             */
/*   Updated: 2023/11/02 20:29:01 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i; 
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return (((char *)haystack));
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return (&((char *)haystack)[i - j]);
			j++;
		}
		else
		{
			if (j != 0)
				i -= j;
			j = 0;
		}
		i++;
	}
	return (NULL);
}
