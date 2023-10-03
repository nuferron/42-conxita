/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:17:38 by nuferron          #+#    #+#             */
/*   Updated: 2023/10/03 16:27:55 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../conxita.h"

int	here_doc(char *key)
{
	char	*line;
	char	*result;
	char	*tmp;

	line = readline("> ");
	tmp = NULL;
	while (line)
	{
		if (ft_strlen(key) == ft_strlen(line) - 1
			&& ft_strncmp(line, key, ft_strlen(key) - 1) == 0)
		{
			break ;
		}
		result = ft_strjoin(tmp, line);
		free(tmp);
		tmp = result;
		free(line);
		line = get_next_line(0);
	}
	free(line);
	printf("%s", result);
	return (0);
}

int main()
{
	//printf("%s", here_doc("eof"));
	here_doc("eof");
}
