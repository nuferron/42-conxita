#include "../../conxita.h"

/*Will print the error message and should return the status,
  but it's not happening right now*/
int	print_errors(char *str)
{
	if (str && !ft_strncmp(str, "\'newline\'", 6))
	{
		ft_dprintf(2, "conxita: %s%s\n", SYNTAX, str);
		return (-1);
	}
	else if (str)
		ft_dprintf(2, "conxita: %s: ", str);
	return (-1);
}
