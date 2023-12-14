/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:04:36 by blvilarn          #+#    #+#             */
/*   Updated: 2023/12/13 19:04:37 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

t_env	*find_last(t_env *env, char *key)
{
	t_env	*last;

	last = NULL;
	while (env && ft_strncmp(key, env->key, ft_strlen(key)))
	{
		last = env;
		env = env->next;
	}
	return (last);
}

static t_env	*yeet_env(t_env *env, char *key)
{
	t_env	*var;
	t_env	*last;

	var = search_env(env, key);
	if (!var)
		return (env);
	last = find_last(env, key);
	if (!last)
		env = var->next;
	else
		last->next = var->next;
	free (var);
	return (env);
}

int	builtin_unset(char **args, t_conxita *all)
{
	int	i;
	int	j;
	int	exit_code;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!is_env(args[i][j]))
			{
				exit_code = 1;
				ft_dprintf(2, "conxita: unset: `%s': not a valid identifier\n",
					args[i]);
				break ;
			}
			j++;
		}
		all->env = yeet_env(all->env, args[i]);
		i++;
	}
	return (exit_code);
}
