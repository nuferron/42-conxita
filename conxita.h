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

#define LINE_DEL "\033[A"

enum	e_arg_type {unk = 0, file = 1, red = 2, arg = 3, cmd = 4};

enum	e_output {stdo = 0, f_trunc = 1, f_append = 2, opipe = 3};
enum	e_input {stdi = 0, infile = 1, ipipe = 2};

typedef struct s_cmd
{
	char			**cmd;
	char			*heredoc;
	char			*infile; //OJU! This is the last file mentioned!
	int				infd;
	char			*outfile; // OJU! This is the last file mentioned! The others must be created but not written
	int				outfd;
	enum e_output	output;
	enum e_input	input;
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

/*Signal Handler*/
void		signal_hook(int sig);
void		setup_signals(void);

/*Prompt Handler*/
int			handle_prompt(char *prompt);

//Tokenizer
t_oken		*glorified_ft_split(char *prompt);
int			get_token_num(char *prompt);
void		populate_tokens(char *prompt, t_oken *tokens);
void		s_quote_len(char *prompt, int *i, int *len);
void		d_quote_len(char *prompt, int *i, int *len);

/*Conxita Handler*/
void		print_conxita(void);

/*Bool Utils*/
void		b_invert(bool *b);

/*Environment Utils*/
char		*search_env(char **env, char *key);
int			len_to_char(char *str, char c);
char		*mini_split(char *path, int count);
int			path_count(const char *s, char c);

/*Chevrons Functions*/
int			here_doc(t_cmd *cmd, char *key);
int			open_chev(t_cmd *cmd);
int			close_chev(t_cmd *cmd, int append);
