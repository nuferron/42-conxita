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

static int	is_valid_export(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!is_env(arg[i]) && arg[i] != '=')
			return (0);
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (1);
}

static int	set_env(char **args, t_env *env)
{
	int		i;
	int		exit_code;

	i = 0;
	exit_code = 0;
	while (args[i])
	{
		if (!is_valid_export(args[i]))
		{
			exit_code = 1;
			ft_dprintf(2, "conxita: export: `%s': not a valid identifier\n",
				args[i]);
			i++;
			continue ;
		}
		env_addback(&env, new_env(args[i]));
		i++;
	}
	return (exit_code);
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
}
