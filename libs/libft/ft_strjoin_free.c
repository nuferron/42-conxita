/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:25:54 by blvilarn          #+#    #+#             */
/*   Updated: 2023/05/29 16:25:37 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *dst, char *src)
{
	int		i;
	int		j;
	int		dst_len;
	int		src_len;
	char	*result;

	if (!dst && !src)
		return (deep_free(&dst));
	i = -1;
	j = -1;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	result = ft_calloc(dst_len + src_len + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (++i < dst_len)
		result[i] = dst[i];
	while (++j < src_len)
		result[i++] = src[j];
	deep_free(&dst);
	return (result);
}
