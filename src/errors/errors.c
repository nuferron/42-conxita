/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:35:56 by nuferron          #+#    #+#             */
/*   Updated: 2023/12/07 15:35:58 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

/*Will print the error message and should return the status,
  but it's not happening right now*/
int	print_errors(char *str)
{
	ft_dprintf(2, "conxita: ");
	if (str && !ft_strncmp(str, "syntax", 6))
	{
		ft_dprintf(2, "%s\n", str);
		return (-1);
	}
	else if (str)
		ft_dprintf(2, "%s: ", str);
	perror(NULL);
	return (-1);
}
