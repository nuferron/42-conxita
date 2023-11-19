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
	return (result);
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
	write(pipe_h[1], "\0", 1);
	free(tmp);
	free(line);
	return (pipe_h[0]);
}

int	exec_heredoc(t_cmd *cmd)
{
	int		i;
	int		error;
	int		len;
	char	buffer[10];

	i = 0;
	error = 0;
	len = cmd[0].len;
	while (i < len)
	{
		if (cmd[i].heredoc)
			error = here_doc(cmd[i].heredoc);
		i++;
	}
	dprintf(2, "exec heredoc error %d\n", error);
	if (error != -1)
	{
		while (1)
		{
			len = read(error, buffer, 9);
			buffer[len] = '\0';
			write(1, buffer, len);
			if (buffer[len - 1] == '\0')
				return (1);
		}
	}
	if (error == -1)
		return (-1);
	return (0);
}
