/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:10:13 by blvilarn          #+#    #+#             */
/*   Updated: 2023/05/29 16:28:11 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		s1_len;
	int		s2_len;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	i = -1;
	j = -1;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (++i < s1_len)
		result[i] = s1[i];
	while (++j < s2_len)
		result[i++] = s2[j];
	return (result);
}
