#include "../../conxita.h"

char	*go_home(t_env *env)
{
	char	*user;

	user = search_env(env, "USER");
	if (!user)
		return (NULL);
	user = ft_strjoin("/Users/", user);
	if (!user)
		exit((unsigned char)print_errors(NULL));
	return (user);
}

int	builtin_cd(char **args, t_env *env)
{
	int		argn;
	char	*home;

	argn = get_arg_number(args);
	if (argn > 1)
	{
		ft_dprintf(2, "conxita: cd: too many arguments\n");
		return (1);
	}
	if (argn == 0)
	{
		home = go_home(env);
		if (chdir(home) == -1)
		{
			ft_dprintf(2, "conxita: cd: HOME not set\n");
			return (1);
		}
		free(home);
		return (0);
	}
	if (chdir(args[0]) == -1)
		return (print_errors("cd"));
	return (0);
}
