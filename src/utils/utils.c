/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:38:29 by nuferron          #+#    #+#             */
/*   Updated: 2023/12/13 17:21:57 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

char	*ft_strtrim_free(char *s1, char *set)
{
	char	*trimmed_str;

	trimmed_str = ft_strtrim(s1, set);
	free(s1);
	return (trimmed_str);
}

/*Waits for the last child process and returns its status ($?)*/
int	ft_waitpid(int pid, int len)
{
	int	status;
	int	code;
	int	wait;
	int	i;

	i = -1;
	code = -1;
	while (++i <= len)
	{
		wait = waitpid(-1, &status, 0);
		if (wait == pid)
		{
			if (WIFEXITED(status))
				code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				code = WTERMSIG(status);
			else if (WIFSTOPPED(status))
				code = WSTOPSIG(status);
		}
	}
	return (code);
}
