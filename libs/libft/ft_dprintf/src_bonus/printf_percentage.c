/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_percentage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:06:10 by nuferron          #+#    #+#             */
/*   Updated: 2023/11/29 15:28:13 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

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
