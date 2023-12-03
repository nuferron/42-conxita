#include "../../conxita.h"

int	builtin_exit(char **args, t_conxita *all)
{
	int	argn;

	argn = get_arg_number(args);
	printf("EXIT: argn %d\n", argn);
	if (!argn)
		exit(all->exit);
	printf("EXIT: args %s\n", args[0]);
	if (!ft_isnum(args[0]))
	{
		ft_dprintf(2, "conxita: cd: %s: numeric argument required", args[0]);
		exit(all->exit);
	}
	if (argn > 1)
		return (1);
	printf("EXIT: atoi args |%s|\t%d\n", args[0], ft_atoi(args[0]));
	exit (ft_atoi(args[0]));
}
