/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:28:44 by blvilarn          #+#    #+#             */
/*   Updated: 2023/12/13 19:29:27 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h" 

int	get_arg_len(char *prompt, int i)
{
	int	len;

	len = 0;
	while (!ft_strchr("<>| ", prompt[i]))
	{
		if (prompt[i] == '\'')
			s_quote_len(prompt, &i, &len);
	}
	return (len);
}
