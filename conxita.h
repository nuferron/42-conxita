#pragma once
#define READLINE_LIBRARY
#include "libs/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <curses.h>
#include <errno.h>
#include <term.h>
#include <tcl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "libs/readline/readline.h"
#include "libs/readline/history.h"

#define LINE_DEL	"\033[A"
#define SYNTAX		"syntax error near unexpected token"

enum	e_arg_type {red = 0, arg = 1};

enum	e_output {stdo = 0, opipe = 1, f_trunc = 2, f_append = 3};
enum	e_input {stdi = 0, ipipe = 1, infile = 2, heredoc = 3};

typedef struct s_cmd
{
	char			**cmd;
	char			*heredoc;
	char			*infile;  //! OJU! This is the last file mentioned!
	int				infd;
	char			*outfile; //! OJU! This is the last file mentioned! The others must be created but not written
	int				outfd;
	enum e_output	output;
	enum e_input	input;
	int				len;
}	t_cmd;

typedef struct s_redir
{
	int		fd_pipe[2];
	int		fdr_aux;
	int		saved_std[2];
}	t_redir;

typedef struct s_parsing
{
	bool	o_simple;
	bool	o_double;
	t_cmd	*cmd;
}	t_parsing;

typedef struct s_oken
{
	enum e_arg_type	type;
	char			*val;
}	t_oken;

typedef struct s_env
{
	char	*key;
	char	*value;
	void	*next;
}	t_env;

/*Signal Handler*/
void	signal_hook(int sig);
void	setup_signals(void);

/*Prompt Handler*/
int		handle_prompt(char *prompt, t_env *env);

/*Tokenizer*/
t_oken	*glorified_ft_split(char *prompt, t_env *env);
int		get_token_num(char *prompt);
t_oken	*generate_tokens(char *prompt, int token_num);
void	quote_len(char *prompt, int *i, int *len);
void	fill_quotes(char *prompt, t_oken *token, int *i, int *j);
char	*expand_env(t_env *env, char *prompt);
char	*replace_variable(char *str, char *old, char *new);
void	*free_the_tokens(t_oken *tokens);

/*Conxita Handler*/
void	print_conxita(void);

/*Utils*/
void	b_invert(bool *b);
char	*ft_strtrim_free(char *s1, char *set);
int		is_builtin(char *str);

/*Environment Utils*/
char	*search_env(t_env *env, char *key);
t_env	*env_to_lst(char **env);

/*Length Utils*/
int		arg_count(t_oken *token, int start);
int		cmd_count(t_oken *token, int i);
int		mat_len(char **mat);
int		path_count(const char *str, char sep);

/*Initializing Utils*/
int		init_cmd_cmd(t_oken *token, t_cmd *cmd, int i, t_env *env);
int		init_chev_output(t_oken *token, t_cmd *cmd, int *i);
int		init_chev_input(t_oken *token, t_cmd *cmd, int *i);
int		init_cmd_red(t_oken *token, t_cmd *cmd, int *i);
void	init_pipe(t_cmd *cmd, int is_pipe);
t_redir	*init_redir(void);

/*Path Utils*/
char	*minisplit(char *path, int count);

/*Chevrons Functions*/
t_cmd	*token_to_cmd(t_oken *token, t_env *env);
t_redir	*init_redir(void);
int		cmd_count(t_oken *token, int i);
int		ft_waitpid(int pid, int len);

/*Execution*/
int		lets_execute(t_cmd *cmd, t_redir *redir, t_env *env, int len);
int		exec_heredoc(t_cmd *cmd);

/*Errors*/
int		print_errors(char *str); // error code 258 for syntax error near unexpected token '|' // 'newline'
