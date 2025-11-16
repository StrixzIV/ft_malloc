/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:44:29 by jikaewsi          #+#    #+#             */
/*   Updated: 2024/08/30 08:57:44 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H  

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Memory handling

void	*ft_calloc(size_t count, size_t size);
int		ft_memcmp(const void *a, const void *b, size_t n);
void	*ft_memset(void *bytes, int character, size_t length);
void	*ft_memchr(const void *bytes, int character, size_t n);
void	*ft_memcpy(void *destination, const void *source, size_t n);
void	*ft_memmove(void *destination, const void *source, size_t length);

// Bytes manipulation

void	ft_bzero(void *bytes, size_t n);

// Character manipulation

int		ft_tolower(int character);
int		ft_toupper(int character);

// Character checker functions

int		ft_isascii(int character);
int		ft_isprint(int character);
int		ft_isalpha(int character);
int		ft_isdigit(int character);
int		ft_isalnum(int character);

// String functions

size_t	ft_strlen(const char *string);
char	*ft_strdup(const char *source);
int		ft_strncmp(const char *a, const char *b, size_t n_character);
size_t	ft_strlcpy(char *destination, const char *source, size_t size);
size_t	ft_strlcat(char *destination, const char *source, size_t n);
char	*ft_strchr(const char *string, int character);
char	*ft_strrchr(const char *string, int character);
char	*ft_strnstr(const char *string, const char *pattern, size_t length);
char	*ft_strjoin(const char *a, const char *b);
char	*ft_strtrim(const char *string, const char *charset);
char	*ft_substr(const char *string, unsigned int start_idx, size_t length);
char	*ft_strmapi(const char *string, char (*function)(unsigned int, char));
void	ft_striteri(char *string, void (*function)(unsigned int, char*));
char	**ft_split(char const *string, char delimiter);

// Conversion functions

char	*ft_itoa(int number);
int		ft_atoi(const char *string);

// Display functions

void	ft_putnbr_fd(int number, int fd);
void	ft_putchar_fd(char character, int fd);
void	ft_putstr_fd(const char *string, int fd);
void	ft_putendl_fd(const char *string, int fd);

// Linked list (Bonus)

size_t	ft_lstsize(t_list *list);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *node);
void	ft_lstadd_front(t_list **list, t_list *node);
void	ft_lstadd_back(t_list **list, t_list *node);
void	ft_lstclear(t_list **list, void (*del_func)(void*));
void	ft_lstdelone(t_list *list, void (*del_func)(void*));
void	ft_lstiter(t_list *node, void (*function)(void *));
t_list	*ft_lstmap(t_list *node, void *(*func)(void *), void (*del)(void *));

#endif
