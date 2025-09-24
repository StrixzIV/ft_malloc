CC = cc
C_FLAGS = -Wall -Wextra -Werror

LIBC = ar rcs

SOURCE_PATH = ./
INCLUDE_PATH = ./

CFILES =	ft_bzero.c      ft_isdigit.c    ft_memset.c     ft_putendl_fd.c ft_putstr_fd.c  ft_strdup.c     ft_strncmp.c 		\
			ft_isalnum.c    ft_isprint.c    ft_strlcat.c    ft_isalpha.c    ft_putchar_fd.c ft_putnbr_fd.c  ft_strlen.c			\
			ft_tolower.c 	ft_isascii.c    ft_memcpy.c     ft_toupper.c 	ft_memcmp.c		ft_memmove.c	ft_memchr.c			\
			ft_strchr.c		ft_strrchr.c	ft_atoi.c		ft_calloc.c  	ft_itoa.c		ft_strlcpy.c	ft_strjoin.c		\
			ft_strnstr.c	ft_substr.c		ft_strtrim.c	ft_strmapi.c	ft_striteri.c	ft_split.c
			

BONUS = 	ft_lstnew_bonus.c		ft_lstsize_bonus.c		ft_lstdelone_bonus.c		ft_lstclear_bonus.c		ft_lstiter_bonus.c	ft_lstlast_bonus.c	ft_lstadd_front_bonus.c	\
			ft_lstadd_back_bonus.c	ft_lstmap_bonus.c

SOURCES := $(addprefix $(SOURCE_PATH), $(CFILES))
BONUS_SOURCES := $(addprefix $(SOURCE_PATH), $(BONUS))
NAME = libft.a
OBJS = $(SOURCES:.c=.o)
OBJBS = $(BONUS_SOURCES:.c=.o)

all: $(NAME)

%.o: %.c libft.h Makefile
	$(CC) $(C_FLAGS) -c $< -o $@

bonus:
	@make BONUS_F=1 --no-print-directory

ifeq ($(BONUS_F), 1)

$(NAME): $(OBJS) $(OBJBS)
	$(LIBC) $(NAME) $(OBJS) $(OBJBS)

else

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $(OBJS)

endif

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SOURCES) $(BONUS_SOURCES)
	$(CC) -nostartfiles -shared -o libft.so $(OBJS) $(OBJBS)

clean:
	rm -f $(OBJS) $(OBJBS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
