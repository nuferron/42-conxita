/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conxita.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:48:44 by blvilarn          #+#    #+#             */
/*   Updated: 2023/10/05 20:34:44 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

int	main(void)
{
	char	*prompt;
	char	*prompt_text;

	print_conxita();
	setup_signals();
	prompt_text = ft_strjoin(getenv("USER"), "@conxita$ ");
	while ("Conxita")
	{
		prompt = readline(prompt_text);
		handle_prompt(ft_strtrim(prompt, " "));
	}
	return (0);
}
