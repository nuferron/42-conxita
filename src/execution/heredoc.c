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
int	here_doc(t_redir *redir, char *key)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	tmp = NULL;
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
	write(redir->fd_pipe[1], tmp, ft_strlen(tmp));
	free(tmp);
	free(line);
	return (0);
}
