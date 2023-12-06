#include "../../conxita.h"

static void	print_export(t_env *env_lst)
{
	int		i;
	char	**env;

	i = 0;
	env = env_to_mat(env_lst, 1);
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	free (env);
}

static int	set_env(char **args, t_env *env)
{
	int		i;
	int		j;
	int		exit_code;

	i = 0;
	j = 0;
	(void)env;
	exit_code = 0;
	while (args[i])
	{
		while (args[i][j])
		{
			if (!is_env(args[i][j]))
			{
				exit_code = 1;
				ft_dprintf(2, "conxita: export: %s: not a valid identifier\n");
				break ;
			}
		}
	}
	return (42);
}

int	builtin_export(char **args, t_env *env_lst)
{
	int	argn;

	argn = get_arg_number(args);
	if (argn == 0)
	{
		print_export(env_lst);
		return (0);
	}
	return (set_env(args, env_lst));
	return (0);
}
