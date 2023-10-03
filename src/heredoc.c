/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:17:38 by nuferron          #+#    #+#             */
/*   Updated: 2023/10/03 20:15:18 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../conxita.h"

int	here_doc(char *key)
{
	char	*line;
	int		fd_pipe[2];

	line = readline("> ");
	if (pipe(fd_pipe) == -1)
		return (-1);
	while (line)
	{
		if (ft_strlen(key) == ft_strlen(line)
			&& ft_strncmp(line, key, ft_strlen(key) - 1) == 0)
			break ;
		write(fd_pipe[1], &line, ft_strlen(line));
		free(line);
		line = readline("> ");
	}
	free(line);
	return (0);
}

