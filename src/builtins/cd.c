#include "../../conxita.h"

int	builtin_cd(char **args, t_env *env)
{
	int		argn;
	char	*home;

	argn = get_arg_number(args);
	printf("%i\n", argn);
	if (argn > 1)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (argn == 0)
	{
		home = search_env(env, "HOME");
		if (!home)
		{
			printf("cd: HOME not set");
			return (1);
		}
		if (chdir(home) == -1)
			return (1);
		return (0);
	}
	if (chdir(args[0]) == -1)
		return (1);
	return (0);
}
