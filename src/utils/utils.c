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
	int	wait;
	int	i;

	i = -1;
	while (++i <= len)
	{
		wait = waitpid(-1, &status, WUNTRACED | WCONTINUED);
		if (wait == -1)
			return (print_errors("waitpid"));
		if (wait == pid)
		{
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				return (WTERMSIG(status));
			else if (WIFSTOPPED(status))
				return (WSTOPSIG(status));
		}
	}
	return (0);
}
