#include "../../conxita.h"

int	builtin_exit(char **args, t_conxita *all)
{
	int	argn;

	ft_printf("exit\n");
	argn = get_arg_number(args);
	if (!argn)
		exit(all->exit);
	if (!ft_isnum(args[0]))
	{
		ft_dprintf(2, "conxita: exit: %s: numberic argument required\n", \
			args[0]);
		exit(255);
	}
	if (argn > 1)
	{
		ft_dprintf(2, "conxita: exit: too many arguments\n");
		return (1);
	}
	exit (ft_atoi(args[0]));
}
