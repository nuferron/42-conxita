#include "../../conxita.h"

/*Returns 1 if the input is a valid flag and 0 if it's not*/
int	is_flag(char *flag)
{
	int	i;

	i = 1;
	if (flag[0] == '-' && flag[1] == 'n')
	{
		while (flag[i] && flag[i] == 'n')
			i++;
		if (flag[i] == '\0')
			return (1);
	}
	return (0);
}

int	builtin_echo(char **args)
{
	int	flag;
	int	i;
	int	argn;

	flag = 0;
	i = 0;
	argn = get_arg_number(args);
	while (i < argn && is_flag(args[i]))
	{
		flag = 1;
		i++;
	}
	while (i < argn)
	{
		printf("%s", args[i++]);
		if (i < argn)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
