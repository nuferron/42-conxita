/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dpf_percentage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blai <blai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:06:10 by nuferron          #+#    #+#             */
/*   Updated: 2023/12/22 04:11:22 by blai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	percentage_bonus(int fd, t_flags *flags)
{
	char	*final_str;
	char	*str;
	int		nbytes;

	str = ft_strdup("%");
	if (!str)
		return (-1);
	final_str = add_padding(str, flags);
	free(str);
	if (!final_str)
		return (-1);
	nbytes = write(fd, final_str, ft_strlen(final_str));
	free(final_str);
	if (nbytes == -1)
		return (-1);
	return (nbytes);
}
