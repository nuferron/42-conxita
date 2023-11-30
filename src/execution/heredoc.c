#include "../../conxita.h"

/*Replicates the heredoc functionality (<<)*/
int	here_doc(char *key)
{
	char	*line;
	int		pipe_h[2];

	if (pipe(pipe_h) == -1)
		return (print_errors(NULL));
	line = readline("> ");
	while (line)
	{
		if (ft_strlen(key) == ft_strlen(line)
			&& ft_strncmp(line, key, ft_strlen(key) - 1) == 0)
			break ;
		write(pipe_h[1], line, ft_strlen(line));
		write(pipe_h[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(pipe_h[1]);
	return (pipe_h[0]);
}

int	exec_heredoc(t_cmd *cmd, char *key)
{
	cmd->fd_hd = here_doc(key);
	return (0);
}
