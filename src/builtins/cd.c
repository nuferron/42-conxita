#include "../../conxita.h"

int	builtin_cd(char **args, t_env *env)
{
	int		argn;

	argn = get_arg_number(args);
	if (argn > 1)
	{
		ft_dprintf(2, "conxita: cd: too many arguments\n");
		return (1);
	}
	if (argn == 0)
	{
		if (chdir(search_env(env, "HOME")->value) == -1)
		{
			ft_dprintf(2, "conxita: cd: HOME not set\n");
			return (1);
		}
		return (0);
	}
	if (chdir(args[0]) == -1)
		return (-print_errors("cd: "));
	return (0);
}
