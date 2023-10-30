#include "../../conxita.h"

int	print_errors(char *str)
{
	if (str)
		printf("conxita: %s %s\n", SYNTAX, str);
		return (258);
	perror("conxita");
	return (-1);
}
