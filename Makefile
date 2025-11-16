CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fPIC
LDFLAGS = -pthread

SOURCE_PATH = srcs/
INCLUDE_PATH = includes/
BUILD_PATH = build/

CFILES = 	align.c \
			allocate.c \
			free.c \
			ft_memcpy.c \
			ft_putchar_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_strlen.c \
			malloc.c \
			realloc.c \
			show_alloc_utils.c \
			show_alloc_mem.c \
			show_alloc_mem_ex.c \
			tracker.c

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CFLAGS += -I$(INCLUDE_PATH)
SOURCES = $(addprefix $(SOURCE_PATH), $(CFILES))
OBJS = $(addprefix $(BUILD_PATH), $(CFILES:.c=.o))
HEADERS = $(addprefix $(INCLUDE_PATH), ft_malloc.h)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking library: $(NAME)"
	@$(CC) $(LDFLAGS) -shared -o $(NAME) $(OBJS) $(LIBFT_LIBS)
	@echo "Done."

$(BUILD_PATH)%.o: $(SOURCE_PATH)%.c $(HEADERS) Makefile
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "Compiling: $(notdir $<)\n"

clean:
	@echo "Cleaning project object files..."
	@rm -rf $(BUILD_PATH)

fclean: clean
	@echo "Removing library: $(NAME)"
	@rm -f $(NAME)

test: $(NAME)
	@echo "Compiling test executable..."
	@$(CC) main.c -o main -I$(INCLUDE_PATH) -L. -lft_malloc_$(HOSTTYPE)
	@LD_PRELOAD=./$(NAME) ./main

re: fclean all

.PHONY: all clean fclean re test
