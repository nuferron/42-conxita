#include "../conxita.h"

int	chevron(t_mateu *mateu, char *file)
{
	int	fd;
	int	fd_pipe;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (errors(mateu, file));
	if (pipe(fd_pipe) == -1)
		return (errors(mateu, "pipe error"));
	if (dup2(fd_pipe[0], 0) == -1)
		return (errors(mateu, ""));
}
