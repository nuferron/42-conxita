#include "../../conxita.h"

char	*ft_strtrim_free(char *s1, char *set)
{
	char	*trimmed_str;

	trimmed_str = ft_strtrim(s1, set);
	free(s1);
	return (trimmed_str);
}

/*Waits for the last child process and returns its status ($?)*/
int	ft_waitpid(int pid, int len)
{
	int	status;
	int	code;
	int	wait;
	int	i;

	i = -1;
	code = -1;
	while (++i <= len)
	{
		wait = waitpid(-1, &status, WUNTRACED | WCONTINUED);
		if (wait == -1)
			return (print_errors(NULL));
		if (wait == pid)
		{
			if (WIFEXITED(status))
				code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				code = WTERMSIG(status);
			else if (WIFSTOPPED(status))
				code = WSTOPSIG(status);
		}
	}
	return (code);
}

int	get_arg_number(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}
