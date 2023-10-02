/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:40:11 by blvilarn          #+#    #+#             */
/*   Updated: 2022/10/11 11:05:25 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	slen;

	slen = ft_strlen(s);
	if (len > slen)
		len = slen;
	if (!s || start > slen || len == 0)
	{
		str = ft_calloc(1, 1);
		if (!str)
			return (NULL);
		return (str);
	}
	if (slen - start < len)
		len = slen - start;
	str = malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	ft_strlcpy (str, &s[start], len + 1);
	return (str);
}
