CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -pthread

SOURCE_PATH = srcs/
INCLUDE_PATH = includes/
BUILD_PATH = build/

LIBFT_PATH = ./lib/libft
LIBFT_LIBS = $(LIBFT_PATH)/libft.a

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CFILES =	
			
NAME = libft_malloc_$(HOSTTYPE).so

SOURCES := $(addprefix $(SOURCE_PATH), $(CFILES))
OBJS = $(SOURCES:.c=.o)
OBJS_BUILD = $(addprefix build/, $(OBJS))

all: $(BUILD_PATH) $(LIBFT_LIBS) $(NAME)

$(BUILD_PATH):
	@mkdir -p build/

$(LIBFT_LIBS): 
	@echo "Making libft..."
	@make -C $(LIBFT_PATH) bonus -s

build/%.o: %.c Makefile
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"
	
$(NAME): $(OBJS_BUILD)
	$(CC) $(OBJS_BUILD) $(LIBFT_LIBS) $(LDFLAGS) $(HEADERS) -o $(NAME)

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJS) $(OBJBS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -rf build
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
