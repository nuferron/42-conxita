#include "../../conxita.h"

int	path_count(const char *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

int	len_to_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

char	*minisplit(char *path, int count)
{
	int		i;
	int		skip;
	char	*tmp;
	char	*result;

	i = 0;
	skip = 0;
	while (skip < count)
	{
		if (path[i++] == ':')
			skip++;
	}
	tmp = ft_substr(path, i, len_to_char(&path[i], ':'));
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, "/");
	free(tmp);
	return (result);
}
