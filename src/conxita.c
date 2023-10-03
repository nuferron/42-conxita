/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conxita.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:48:44 by blvilarn          #+#    #+#             */
/*   Updated: 2023/10/03 12:37:03 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../conxita.h"

int	main(void)
{
	char	*prompt;

	print_conxita();
	setup_signals();
	while ("Conxita")
	{
		prompt = readline("conxita$ ");
		
		handle_prompt(prompt);
	}
	return (0);
}
