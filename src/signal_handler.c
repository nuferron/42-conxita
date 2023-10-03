/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:10:25 by blvilarn          #+#    #+#             */
/*   Updated: 2023/10/03 12:07:56 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../conxita.h"

void	signal_hook(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == 4)
		printf("THIS ONE");
}

void	setup_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_hook);
	signal(4, signal_hook);
}
