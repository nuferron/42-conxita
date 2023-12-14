/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:04:27 by blvilarn          #+#    #+#             */
/*   Updated: 2023/12/13 19:04:28 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

int	builtin_env(t_env *env_lst)
{
	char	**env;
	int		i;

	env = env_to_mat(env_lst, 0);
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		free(env[i]);
		i++;
	}
	free(env);
	return (0);
}
