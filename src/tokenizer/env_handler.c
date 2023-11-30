#include "../../conxita.h"

static int	is_env_name(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static char	*get_env_name(char *prompt)
{
	int		len;
	int		i;
	char	*name;

	len = 1;
	i = 1;
	while (is_env_name(prompt[len]))
		len++;
	name = ft_calloc(len + 1, sizeof(char));
	if (!name)
	{
		free(prompt);
		return (NULL);
	}
	name[0] = '$';
	while (is_env_name(prompt[i]))
	{
		name[i] = prompt[i];
		i++;
	}
	return (name);
}

static char	*get_val(t_env *env, char *name)
{
	char	*val;

	val = search_env(env, name);
	if (!val)
		return ("");
	return (val);
}

static char	*replace_env(t_env *env, char *prompt, int *i)
{
	char	*new_prompt;
	char	*name;
	char	*val;

	name = get_env_name(&prompt[*i]);
	if (!name)
		return (NULL);
	val = get_val(env, &name[1]);
	new_prompt = replace_variable(prompt, name, val);
	free(name);
	free(prompt);
	if (!new_prompt)
		return (NULL);
	*i += ft_strlen(val) - 1;
	if (*i < 0)
		*i = 0;
	return (new_prompt);
}

//Replaces prompt 
char	*expand_env(t_env *env, char *prompt)
{
	int		i;
	bool	o_quotes;

	i = 0;
	o_quotes = false;
	while (prompt && prompt[i])
	{
		if (prompt[i] == '"')
			b_invert(&o_quotes);
		if ((prompt[i] == '\'' && !o_quotes) || ft_strnstr(&prompt[i], "<<", 2))
			skip_unexpandable(prompt, &i);
		if (prompt[i] == '$' && is_env_name(prompt[i + 1]))
			prompt = replace_env(env, prompt, &i);
		if (prompt && prompt[i])
			i++;
	}
	return (prompt);
}
