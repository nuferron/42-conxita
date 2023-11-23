#include "../../conxita.h"

/*Joins 3 strings and frees the allocated strings (1 and 2)*/
char	*ft_strjoin3_free(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	result = ft_strjoin(tmp, str3);
	free(tmp);
	tmp = ft_strjoin(result, "\0");
	free(result);
	return (tmp);
}

/*Replicates the heredoc functionality (<<)*/
int	here_doc(char *key)
{
	char	*line;
	char	*tmp;
	int		pipe_h[2];

	line = readline("> ");
	tmp = NULL;
	if (pipe(pipe_h) == -1)
		return (-1);
	while (line)
	{
		if (ft_strlen(key) == ft_strlen(line)
			&& ft_strncmp(line, key, ft_strlen(key) - 1) == 0)
			break ;
		tmp = ft_strjoin3_free(tmp, line, "\n");
		if (!tmp)
			return (print_errors(NULL));
		line = readline("> ");
	}
	write(pipe_h[1], tmp, ft_strlen(tmp));
	free(tmp);
	free(line);
	close(pipe_h[1]);
	return (pipe_h[0]);
}

int	exec_heredoc(t_cmd *cmd)
{
	int		i;
	int		read_fd;
	int		len;

	i = 0;
	read_fd = 0;
	len = cmd[0].len;
	while (i < len)
	{
		if (cmd[i].heredoc)
			read_fd = here_doc(cmd[i].heredoc);
		i++;
	}
	if (read_fd == -1)
		return (-1);
	return (read_fd);
}
