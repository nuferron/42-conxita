/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:41:33 by nuferron          #+#    #+#             */
/*   Updated: 2023/12/13 17:56:26 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

int	here_doc_wrapper(char *key)
{
	int	pipe_h[2];
	int	pid;
	int	pid_code;

	if (pipe(pipe_h) == -1)
		return (print_errors(NULL));
	pid = fork();
	set_signals_ignore_all();
	if (pid == 0)
		here_doc(key, pipe_h);
	pid_code = ft_waitpid(pid, 1);
	set_signals_noninteractive();
	if (pid_code == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		pid_code = -1;
	}
	close(pipe_h[1]);
	return (pipe_h[0]);
}

/*Replicates the heredoc functionality (<<)*/
int	here_doc(char *key, int *pipe_h)
{
	char	*line;

	set_signals_heredoc();
	line = readline("> ");
	while (line)
	{
		set_signals_noninteractive();
		if (ft_strlen(key) == ft_strlen(line)
			&& ft_strncmp(line, key, ft_strlen(key)) == 0)
			break ;
		write(pipe_h[1], line, ft_strlen(line));
		write(pipe_h[1], "\n", 1);
		free(line);
		set_signals_heredoc();
		line = readline("> ");
	}
	free(line);
	exit (pipe_h[0]);
}
