/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:34:32 by blvilarn          #+#    #+#             */
/*   Updated: 2022/11/01 18:49:53 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t
	get_lens(const char *s1, const char *set, size_t *prelen, size_t *poslen)
{
	size_t	s1len;

	s1len = ft_strlen(s1);
	while (ft_strchr(set, s1[*prelen]) && s1[*prelen] != '\0')
		*prelen = *prelen + 1;
	while (ft_strchr(set, s1[s1len - *poslen - 1]) && *poslen < s1len)
		*poslen = *poslen + 1;
	if (*prelen == s1len)
		*poslen = 0;
	return (s1len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1len;
	size_t	prelen;
	size_t	poslen;
	char	*s2;

	prelen = 0;
	poslen = 0;
	if (!s1)
		return (NULL);
	if (s1[0] == '\0' || set[0] == '\0' || !set)
	{
		s2 = ft_strdup(s1);
		if (!s2)
			return (NULL);
		return (s2);
	}
	s1len = get_lens(s1, set, &prelen, &poslen);
	s2 = malloc(s1len - prelen - poslen + 1);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, &s1[prelen], s1len - poslen - prelen + 1);
	return (s2);
}
