/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:17:38 by nuferron          #+#    #+#             */
/*   Updated: 2023/10/03 16:57:36 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../conxita.h"

int	getting_doc(char *key)
{
	char	*line;
	char	*result;
	char	*tmp;

	line = readline("> ");
	tmp = NULL;
	while (line)
	{
		if (ft_strlen(key) == ft_strlen(line)
			&& ft_strncmp(line, key, ft_strlen(key) - 1) == 0)
			break ;
		result = ft_strjoin(tmp, line);
		free(line);
		free(tmp);
		tmp = result;
		result = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = result;
		line = readline("> ");
	}
	free(line);
	printf("%s", result);
	return (0);
}

int	here_doc(char *key)
{
	int	fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		return (-1);
	if (dup2(fd_pipe[1], 1))
	return (0);
}

int main()
{
	here_doc("eof");
}
