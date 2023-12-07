/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:41:33 by nuferron          #+#    #+#             */
/*   Updated: 2023/12/07 21:53:33 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

/*Replicates the heredoc functionality (<<)*/
int	here_doc(char *key)
{
	char	*line;
	int		pipe_h[2];

	if (pipe(pipe_h) == -1)
		return (print_errors(NULL));
	//set_signals_heredoc();
	set_signals_interactive();
	line = readline("> ");
	set_signals_noninteractive();
	while (line)
	{
		if (ft_strlen(key) == ft_strlen(line)
			&& ft_strncmp(line, key, ft_strlen(key) - 1) == 0)
			break ;
		write(pipe_h[1], line, ft_strlen(line));
		write(pipe_h[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(pipe_h[1]);
	return (pipe_h[0]);
}
