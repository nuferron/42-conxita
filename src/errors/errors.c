#include "../../conxita.h"

/*Will print the error message and should return the status,
  but it's not happening right now*/
int	print_errors(char *str)
{
	ft_putstr_fd("conxita: ", 2);
	if (str && !ft_strncmp(str, "\'newline\'", 6))
	{
		ft_putstr_fd(SYNTAX, 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	else if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	perror(NULL);
	return (-1);
}
