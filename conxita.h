/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conxita.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:31:13 by blvilarn          #+#    #+#             */
/*   Updated: 2023/10/03 21:57:13 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_cmd
{
	char	*cmd;
	char	*flags;
	int		fd_pipe[2];
	int		fdr_aux;
}			t_cmd;

typedef struct s_parsing
{
	bool			o_simple;
	bool			o_double;
}				t_parsing;

//Signal Handler
void	signal_hook(int sig);
void	setup_signals(void);

//Prompt Handler
int		handle_prompt(char *prompt);

//Conxita Handler
void	print_conxita(void);

//Bool Utils
void	b_invert(bool *b);

// Chevrons Functions
int	here_doc(t_cmd *cmd, char *key);
int	open_chev(t_cmd *cmd, char *file);
int	close_chev(t_cmd *cmd, char *file, int append);
