/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blai <blai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:00:54 by blvilarn          #+#    #+#             */
/*   Updated: 2023/12/22 04:16:25 by blai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_iswhitespace(int c);
int			ft_isnum(char *str);
void		*ft_memset(void *b, int c, size_t len);
int			ft_strlen(const char *s);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);
double		ft_atod(const char *str);
long		ft_atol(const char *str);
long long	ft_atoll(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_free(char *dst, char *src);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int			ft_endswith(char *str, char *end);
int			ft_memcontains(void *mem, int x, int size);
char		*ft_strreplace(char *str, char *old, char *new);

//ft_printf
int			ft_printf(const char *str, ...);
int			print_content(const char *str, va_list ptr, int *i, int *len);
int			ft_putchar(char c, int *i, int *len);
int			ft_putstr(char *s, int *i, int *len);
int			ft_putnbr(long long n, int *i, int *len);
int			putn_b(char *base_array, unsigned long n, int *len, int *i);

//------ft_dprintf------
typedef struct s_printf
{
	char	padd_type;
	char	sign;
	char	hex;
	int		width;
	char	precision;
	int		prec_width;
}	t_flags;

int			ft_dprintf(int fd, char const *format, ...);
int			print_char(int fd, int c);
int			print_string(int fd, char *str);
int			print_num(int fd, int n);
int			print_pointer(int fd, unsigned long long num);
int			print_unsigned_num(int fd, unsigned int num);
int			print_hex_min(int fd, unsigned int dec_num);
int			print_hex_cap(int fd, unsigned int dec_num);

int			ft_dprintf_bonus(int fd, char const *format, ...);
int			is_specifier(char c);

/*FLAGS PRE-PROCESSORS*/
int			eval_flags(char *format, int i, t_flags *flags);
void		default_flags(t_flags *flags);
int			capturing_flags(char *format, int i, t_flags *flags);
int			capturing_flags_char(char *format, int i, t_flags *flags);

/*MAIN FUNCTIONS*/
int			char_bonus(int fd, int c, t_flags *flags);
int			string_bonus(int fd, char *str, t_flags *flags);
int			num_bonus(int fd, int num, t_flags *flags);
int			pointer_bonus(int fd, unsigned long long num, t_flags *flags);
int			unsigned_bonus(int fd, unsigned int num, t_flags *flags);
int			hex_min_bonus(int fd, unsigned int dec_num, t_flags *flags);
int			hex_cap_bonus(int fd, unsigned int dec_num, t_flags *flags);
int			percentage_bonus(int fd, t_flags *flags);

/*FLAG PROCESSORS*/
int			precision_len(char type, int len, t_flags *flags);
int			precision_padding(char *str, int len, int len_precision);
char		*add_padding(char *str, t_flags *flags);
char		*add_sign(char *str, t_flags *flags);
void		sign_to_front(char *str);
char		*add_ox(char *str, t_flags *flags);
void		ox_to_front(char *str, t_flags *flags);

/*LENGTH FUNCTIONS*/
int			unsigned_len(unsigned int num);
int			pointer_len(unsigned long long num);
int			hex_len(unsigned int num);

//----------------

//get_next_line
char		*get_next_line(int fd);
char		*ft_memjoin(char *line, char *buffer, int read_bytes);
int			is_nl_or_null(char *str, int read_bytes);
char		*deep_free(char **str);

#endif
