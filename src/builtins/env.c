#include "../../conxita.h"

int	builtin_env(char **args, t_env *env_lst)
{
	int		argn;
	char	**env;

	if (argn > 0)
		return (exec_cmd(&(all->cmd[1]), all));
}
