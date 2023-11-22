#include "../../conxita.h"

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd->&(cmd[1]), "echo ", 5))
		return (1);
	else if (!ft_strncmp(cmd->&(cmd[1]), "cd ", 3))
		return (1);
	else if (!ft_strncmp(cmd->&(cmd[1]), "pwd ", 4))
		return (1);
	else if (!ft_strncmp(cmd->&(cmd[1]), "export ", 7))
		return (1);
	else if (!ft_strncmp(cmd->&(cmd[1]), "unset ", 6))
		return (1);
	else if (!ft_strncmp(cmd->&(cmd[1]), "env ", 4))
		return (1);
	else if (!ft_strncmp(cmd->&(cmd[1]), "exit ", 5))
		return (1);
	return (0);
}
