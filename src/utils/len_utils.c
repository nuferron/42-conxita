#include "../../conxita.h"

int	arg_count(t_oken *token, int start)
{
	int	count;

	count = 0;
	while (token[start].val && token[start].type == arg)
	{
		start++;
		count++;
	}
	return (count);
}

int	cmd_count(t_oken *token, int i)
{
	int	j;

	j = 0;
	while (token[j].val)
	{
		if (token[j].val[0] == '|')
			i++;
		j++;
	}
	return (i);
}

/*strlen for char ** */
int	mat_len(char **mat)
{
	int	i;

	i = 0;
	while (mat && mat[i])
		i++;
	return (i);
}

int	env_len(t_env *env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i].next)
		i++;
	return (i + 1);
}
