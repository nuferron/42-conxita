#include "../../conxita.h"

static char	*get_env_name(char *prompt)
{
	int		len;
	int		i;
	char	*name;

	len = 1;
	i = 1;
	while (!ft_strchr("<>|$ '\"", prompt[len]))
		len++;
	name = ft_calloc(len + 1, sizeof(char));
	if (!name)
		return (NULL);
	name[0] = '$';
	while (!ft_strchr("<>|$ '\"", prompt[i]))
	{
		name[i] = prompt[i];
		i++;
	}
	return (name);
}

static char	*get_val(char **env, char *name)
{
	char	*val;

	val = search_env(env, name);
	if (!val)
		return ("");
	return (ft_strchr(val, '=') + 1);
}

static char	*replace_env(char **env, char *prompt, int *i)
{
	char	*new_prompt;
	char	*name;
	char	*val;

	name = get_env_name(&prompt[*i]);
	val = get_val(env, &name[1]);
	new_prompt = replace_variable(prompt, name, val);
	*i += ft_strlen(val);
	free(name);
	free(prompt);
	return (new_prompt);
}

//Replaces prompt 
char	*expand_env(char **env, char *prompt)
{
	int		i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'')
		{
			i++;
			while (prompt[i] != '\'')
				i++;
			i++;
		}
		if (prompt[i] == '$' && !ft_strchr("<>|$", prompt[i + 1]))
			prompt = replace_env(env, prompt, &i);
		if (prompt && prompt[i] != '\0')
			i++;
	}
	return (prompt);
}
