#include "../../conxita.h"

int	builtin_cd(char **args, t_env *env)
{
	int		argn;
	char	*error;

	argn = get_arg_number(args);
	if (argn == 0)
	{
		if (chdir(search_env(env, "HOME")->value) == -1)
			return (ft_dprintf(2, "conxita: cd: HOME not set\n"), 1);
		return (0);
	}
	if (!args[0] || !args[0][0])
		return (0);
	if (chdir(args[0]) == -1)
	{
		error = ft_strjoin("cd: ", args[0]);
		print_errors(error);
		free(error);
		return (1);
	}
	return (0);
}
