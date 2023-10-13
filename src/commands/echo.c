#include "../../conxita.h"

/* It's a bit guarrindongo but who cares */

int	is_flag(char *flag)
{
	int	i;

	i = 1;
	if (flag[0] == '-')
	{
		while (flag[i] && flag[i] == 'n')
			i++;
		if (flag[i] == '\0')
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	flag;
	int	i;

	i = 1;
	while (i < argc && is_flag(argv[i]))
	{
		flag = 1;
		i++;
	}
	while (i < argc)
	{
		printf("%s ", argv[i]);
		i++;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
