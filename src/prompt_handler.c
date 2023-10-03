/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:23:30 by blvilarn          #+#    #+#             */
/*   Updated: 2023/10/03 12:25:46 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../conxita.h"

int	handle_prompt(char *prompt)
{
	if (!prompt || !ft_strncmp(prompt, "", 2))
		return (0);
	add_history(prompt);
	if (!ft_strncmp(prompt, "exit", 5))
	{
		free(prompt);
		exit(0);
	}
	if (prompt)
		printf("%s\n", prompt);
	free (prompt);
	return (0);
}
