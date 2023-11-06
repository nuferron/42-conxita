#include "../../conxita.h"

static int	get_len(char *str, char *old, char *new)
{
	int		len;
	char	*pos;

	len = ft_strlen(str);
	pos = ft_strnstr(str, old, ft_strlen(str));
	while (pos)
	{
		len -= ft_strlen(old);
		len += ft_strlen(new);
		pos = ft_strnstr(pos + 1, old, ft_strlen(pos + 1));
	}
	return (len);
}

static void	fill_end(char *str, char *new_str)
{
	while (*str)
	{
		*new_str = *str;
		str++;
		new_str++;
	}
}

static char	*get_pos(char *str, char *old)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			i++;
		}
		while (str[i] == old[j])
		{
			i++;
			if (old[++j] == '\0')
				return (&str[i - j]);
		}
		j = 0;
		if (str[i])
			i++;
	}
	return (NULL);
}

static void replace(char *str, char *new_str, char *old, char *new)
{
	int		i;
	char	*pos;

	i = 0;
	pos = get_pos(str, old);
	while (pos)
	{
		while (str != pos)
			*new_str++ = *str++;
		while (new[i])
		{
			*new_str = new[i];
			i++;
			new_str++;
		}
		i = 0;
		str += ft_strlen(old);
		pos = get_pos(str, old);
	}
	fill_end(str, new_str);
}

char	*replace_variable(char *str, char *old, char *new)
{
	char	*new_str;

	if (!str || !old || !new)
		return (NULL);
	if (!get_pos(str, old))
		return (str);
	new_str = ft_calloc(get_len(str, old, new) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	replace(str, new_str, old, new);
	return (new_str);
}
