/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:54:56 by blvilarn          #+#    #+#             */
/*   Updated: 2023/11/02 20:21:06 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(char *str, char *old, char *new)
{
	int		len;
	char	*pos;

	len = ft_strlen(str);
	pos = ft_strnstr(str, old, ft_strlen(str));
	while (pos)
	{
		len -= ft_strlen(old);
		len += ft_strlen(new);
		pos = ft_strnstr(pos + 1, old, ft_strlen(pos + 1));
	}
	return (len);
}

static void	fill_end(char *str, char *new_str)
{
	while (*str)
	{
		*new_str = *str;
		str++;
		new_str++;
	}
}

static void	replace(char *str, char *new_str, char *old, char *new)
{
	int		i;
	char	*pos;

	i = 0;
	pos = ft_strnstr(str, old, ft_strlen(str));
	while (pos)
	{
		while (str != pos)
		{
			*new_str = *str;
			str++;
			new_str++;
		}
		while (new[i])
		{
			*new_str = new[i];
			i++;
			new_str++;
		}
		i = 0;
		str += ft_strlen(old);
		pos = ft_strnstr(str, old, ft_strlen(str));
	}
	fill_end(str, new_str);
}

char	*ft_strreplace(char *str, char *old, char *new)
{
	char	*new_str;

	if (!str || !old || !new)
		return (NULL);
	if (!ft_strnstr(str, old, ft_strlen(str)))
		return (str);
	new_str = ft_calloc(get_len(str, old, new) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	replace(str, new_str, old, new);
	return (new_str);
}
