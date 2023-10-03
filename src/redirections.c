#include "../conxita.h"

int	chevron(t_parsing *parsing, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (errors();
	if (pipe(fd_pipe) == -1)
		return (errors();
	if (dup2(fd_pipe[0], 0) == -1)
		return ();
	close(fd);
}
