#include "../../conxita.h"

int	print_errors(char *str)
{
	if (str)
	{
		printf("conxita: %s \033[1;36m%s\033[0m\n", SYNTAX, str);
		//return (258);
		return (-1);
	}
	perror("conxita");
	return (-1);
}
