#include "../../conxita.h"

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
		return (1);
	if (!ft_strncmp(cmd, "cd", 2))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 3))
		return (1);
	if (!ft_strncmp(cmd, "export", 6))
		return (1);
	if (!ft_strncmp(cmd, "unset", 5))
		return (1);
	if (!ft_strncmp(cmd, "env", 3))
		return (1);
	if (!ft_strncmp(cmd, "exit", 4))
		return (1);
	return (0);
}
