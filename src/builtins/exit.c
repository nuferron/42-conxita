#include "../../conxita.h"

int	builtin_exit(char **args, t_conxita *all)
{
	int	argn;

	argn = get_arg_number(args);
	if (!argn)
		exit(all->exit);
	if (!ft_isnum(args[0]))
	{
		ft_dprintf(2, "conxita: cd: %s: numberic argument required", args[0]);
		exit(255);
	}
	if (argn > 1)
		return (1);
	exit (ft_atoi(args[1]));
}
