/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:43:52 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/25 17:12:57 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# define HEX_BASE_UP "0123456789ABCDEF"
# define HEX_BASE_LOW "0123456789abcdef"
# define DEC_BASE "0123456789"
# define CONV_TYPES "cspdiuxX"
# define NUMERIC_TYPES "pdiuxX%"
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdarg.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef	struct			s_gnllist
{
	int					fd;
	char				*rest;
	struct s_gnllist	*next;
}						t_gnllist;

typedef struct			s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

typedef struct			s_infos
{
	char				space;
	int					width;
	int					precision;
	char				pos;
	char				conv;
	char				*dot;
	int					trunc;
	ssize_t				(*printer)(int, const void *, size_t);
}						t_infos;

char					*ft_setchr(const char *str, char *charset);
char					*ft_setrchr(char *str, char *charset);
int						ft_strreplace(char *src, char old, char new);
int						ft_replace_charset(char *src, char *charset, char new);
int						ft_isspace(char c);
int						get_next_line(int fd, char **line);
t_infos					check_infos(t_infos infos, va_list *list);
int						handler(t_infos infos, va_list *list);
int						print_dot(t_infos *infos, va_list *list);
int						get_curr_int(va_list *lst);
int						wp_ft_vprintf(char *format,
	ssize_t (*my_write)(int, const void *, size_t), ...);
int						print_space(t_infos *infos, va_list *list);
int						print_space_str(char c, int size,
	ssize_t (*my_write)(int, const void *, size_t));
t_infos					swp_printer(t_infos infos,
	ssize_t (*my_write)(int, const void *, size_t));
int						my_putchar(char c,
	ssize_t (*my_write)(int, const void *, size_t));
char					**ft_getptr(char *str);
char					*get_format(char *format);
int						ft_vprintf(const char *format, va_list *list,
	ssize_t (*my_write)(int, const void *, size_t));
int						print_conv(t_infos infos, va_list *list);
ssize_t					no_write(int filedes, const void *buf, size_t nbyte);
int						print_form(const char *format, va_list *list,
	ssize_t (*my_write)(int, const void *, size_t));
t_infos					get_infos(char *format, va_list *list,
	ssize_t (*my_write)(int, const void *, size_t));
char					*ft_strndup(const char *s1, int n);
char					*get_conv(char *format);
char					**ft_getptr(char *str);
int						ft_putstr_fd(char *s, int fd);
int						ft_printf(const char *format, ...);
int						len_nbr_base_u(size_t nbr, char *base);
int						len_nbr_base_int(int nbr, char *base);
int						ft_putnbr_base_int(int nbr, char *base,
	ssize_t (*my_write)(int, const void *, size_t));
int						ft_putnbr_base_u(size_t nbr, char *base,
	ssize_t (*my_write)(int, const void *, size_t));
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						ft_isprint(int c);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
int						ft_tolower(int c);
int						ft_toupper(int c);
int						ft_atoi(const char *str);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
void					*ft_memccpy(void *dst, const void *s, int c, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memset(void *b, int c, size_t len);
void					ft_putchar_fd(char c, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					*ft_calloc(size_t count, size_t size);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t					ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t					ft_strlen(const char *s);
size_t					ft_strnlen(const char *s, size_t maxlen);
char					*ft_strnstr(const char *haystack,
const char *needle, size_t len);
char					*ft_strrchr(const char *s, int c);
char					*ft_strdup(const char *s1);
char					**ft_split(char const *str, char charset);
char					*ft_strjoin(char const *s1, const char *s2);
char					*ft_substr(char const *s, unsigned int start,
									size_t len);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_itoa(int n);
char					*ft_strmapi(char const *s,
									char (*f)(unsigned int, char));
char					*ft_strchr(const char *str, int c);
t_list					*ft_lstnew(void	*content);
void					ft_lstadd_front(t_list **alst, t_list *new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **alst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstcpy(t_list *lst, void (*del)(void *));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *));
#endif
