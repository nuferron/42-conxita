#include "../../conxita.h"

char	*extract_env_name(char *s, int i)
{
	int		len;
	char	*name;

	len = 0;
	if (s[i] != '$')
		return (NULL);
	i++;
	while (!ft_strchr("'\"<>| ", s[i]))
	{
		len++;
		i++;
	}
	name = ft_calloc(len + 1, sizeof(char));
	if (!name)
		return (NULL);
	len = 0;
	i += len;
	while (!ft_strchr("'\"<>| ", s[i]))
	{
		name[len] = s[i];
		len++;
		i++;
	}
	return (name);
}
