/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:16:22 by blvilarn          #+#    #+#             */
/*   Updated: 2023/09/05 11:48:46 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
		i++;
	}
	if ((s1[i] == '\0' && s2[i] != '\0') || (s2[i] == '\0' && \
		s1[i] != '\0'))
	{
		if (i != n)
			return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
	}
	return (0);
}
