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
