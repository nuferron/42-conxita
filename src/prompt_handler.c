/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:23:30 by blvilarn          #+#    #+#             */
/*   Updated: 2023/10/03 16:14:31 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../conxita.h"

int	handle_prompt(char *prompt)
{
	if (!prompt)
	{
		printf("\033[A");
		printf("%s\n", "conxita$ exit");
		exit(0);
	}
	if (!ft_strncmp(prompt, "", 2))
	{
		free(prompt);
		return (0);
	}
	add_history(prompt);
	if (!ft_strncmp(prompt, "exit", 5))
	{
		free(prompt);
		printf("%s\n", "exit");
		exit(0);
	}
	if (!ft_strncmp(prompt, "conxita", 8))
		print_conxita();
	else if (prompt)
		printf("%s\n", prompt);
	free (prompt);
	return (0);
}
