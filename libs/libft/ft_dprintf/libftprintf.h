/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:01:32 by nuferron          #+#    #+#             */
/*   Updated: 2023/11/29 16:29:56 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include "../libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_printf
{
	char	padd_type;
	char	sign;
	char	hex;
	int		width;
	char	precision;
	int		prec_width;
}	t_flags;

int		ft_dprintf(int fd, char const *format, ...);
int		print_char(int fd, int c);
int		print_string(int fd, char *str);
int		print_num(int fd, int n);
int		print_pointer(int fd, unsigned long long num);
int		print_unsigned_num(int fd, unsigned int num);
int		print_hex_min(int fd, unsigned int dec_num);
int		print_hex_cap(int fd, unsigned int dec_num);

/***********************  BONUS  ************************/

int		ft_dprintf_bonus(int fd, char const *format, ...);
int		is_specifier(char c);

/*FLAGS PRE-PROCESSORS*/
int		eval_flags(char *format, int i, t_flags *flags);
void	default_flags(t_flags *flags);
int		capturing_flags(char *format, int i, t_flags *flags);
int		capturing_flags_char(char *format, int i, t_flags *flags);

/*MAIN FUNCTIONS*/
int		char_bonus(int fd, int c, t_flags *flags);
int		string_bonus(int fd, char *str, t_flags *flags);
int		num_bonus(int fd, int num, t_flags *flags);
int		pointer_bonus(int fd, unsigned long long num, t_flags *flags);
int		unsigned_bonus(int fd, unsigned int num, t_flags *flags);
int		hex_min_bonus(int fd, unsigned int dec_num, t_flags *flags);
int		hex_cap_bonus(int fd, unsigned int dec_num, t_flags *flags);
int		percentage_bonus(int fd, t_flags *flags);

/*FLAG PROCESSORS*/
int		precision_len(char type, int len, t_flags *flags);
int		precision_padding(char *str, int len, int len_precision);
char	*add_padding(char *str, t_flags *flags);
char	*add_sign(char *str, t_flags *flags);
void	sign_to_front(char *str);
char	*add_ox(char *str, t_flags *flags);
void	ox_to_front(char *str, t_flags *flags);

/*LENGTH FUNCTIONS*/
int		unsigned_len(unsigned int num);
int		pointer_len(unsigned long long num);
int		hex_len(unsigned int num);

#endif
