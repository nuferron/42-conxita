#include "../../conxita.h"

int	builtin_cd(char **args)
{
	int		argn;

	argn = get_arg_number(args);
	if (argn > 1)
	{
		printf("cd: too many arguments");
		return (1);
	}
	if (argn == 0)
	{
		if (chdir('~') == -1)
			return (1);
		return (0);
	}
	if (chdir(args[0] == -1))
		return (1);
	return (0);
}
