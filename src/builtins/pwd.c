#include "../../conxita.h"

int	builtin_pwd(char **args)
{
	char	*pwd;

	if (args)
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
