#include "../../conxita.h"

/*Will print the error message and should return the status,
  but it's not happening right now*/
int	print_errors(char *str)
{
	if (str)
	{
		printf("conxita: %s \033[1;36m%s\033[0m\n", SYNTAX, str);
		return (-1);
	}
	perror("conxita");
	return (-1);
}
