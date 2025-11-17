CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fPIC
LDFLAGS = -pthread

SOURCE_PATH = srcs/
INCLUDE_PATH = includes/

LIBFT_PATH = libft/
BUILD_PATH = build/

CFILES = 	align.c \
			allocate.c \
			free.c \
			malloc.c \
			realloc.c \
			show_alloc_utils.c \
			show_alloc_mem.c \
			show_alloc_mem_ex.c \
			tracker.c \
			debug.c

TEST_BASIC = test_basic
TEST_EDGE = test_edge_cases
TEST_FRAG = test_fragmentation
TEST_ALIGN = test_alignment
TEST_THREAD = test_multithread

TESTS = $(TEST_BASIC) $(TEST_EDGE) $(TEST_FRAG) $(TEST_ALIGN) $(TEST_THREAD)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LIBFT = $(LIBFT_PATH)libft.a
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

NAME = libft_malloc_$(HOSTTYPE).so
LDNAME = libft_malloc.so

CFLAGS += -I$(INCLUDE_PATH)
SOURCES = $(addprefix $(SOURCE_PATH), $(CFILES))
OBJS = $(addprefix $(BUILD_PATH), $(CFILES:.c=.o))
HEADERS = $(addprefix $(INCLUDE_PATH), ft_malloc.h)

all: $(NAME)

$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFT_PATH) bonus --no-print-directory

$(NAME): $(LIBFT) $(OBJS)
	@echo "Linking library: $(NAME)"
	@$(CC) $(LDFLAGS) -shared -o $(NAME) $(OBJS) $(LIBFT_FLAGS)
	@ln -sf $(NAME) $(LDNAME)
	@echo "Done."

$(BUILD_PATH)%.o: $(SOURCE_PATH)%.c $(HEADERS) Makefile
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "Compiling: $(notdir $<)\n"

clean:
	@echo "Cleaning project object files..."
	@rm -rf $(BUILD_PATH)
	@rm -f $(NAME) $(LDNAME) $(TESTS)
	@make -C $(LIBFT_PATH) clean --no-print-directory

fclean: clean
	@echo "Removing library: $(NAME)"
	@make -C $(LIBFT_PATH) fclean --no-print-directory

$(TEST_BASIC): $(NAME)
	@echo "$(YELLOW)Building $@...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $(TESTS_PATH)$@.c -I$(INCLUDE_PATH) -L. -lft_malloc_$(HOSTTYPE) $(LIBFT_FLAGS)

$(TEST_EDGE): $(NAME)
	@echo "$(YELLOW)Building $@...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $(TESTS_PATH)$@.c -I$(INCLUDE_PATH) -L. -lft_malloc_$(HOSTTYPE) $(LIBFT_FLAGS)

$(TEST_FRAG): $(NAME)
	@echo "$(YELLOW)Building $@...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $(TESTS_PATH)$@.c -I$(INCLUDE_PATH) -L. -lft_malloc_$(HOSTTYPE) $(LIBFT_FLAGS)

$(TEST_ALIGN): $(NAME)
	@echo "$(YELLOW)Building $@...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $(TESTS_PATH)$@.c -I$(INCLUDE_PATH) -L. -lft_malloc_$(HOSTTYPE) $(LIBFT_FLAGS)

$(TEST_THREAD): $(NAME)
	@echo "$(YELLOW)Building $@...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $(TESTS_PATH)$@.c -I$(INCLUDE_PATH) -L. -lft_malloc_$(HOSTTYPE) $(LIBFT_FLAGS)

run_test_%: test_%
	@echo "\n$(GREEN)======================================$(RESET)"
	@echo "$(GREEN)Running $<$(RESET)"
	@echo "$(GREEN)======================================$(RESET)"
	@LD_LIBRARY_PATH=.:$(LIBFT_PATH) ./$< || echo "$(RED)Test failed!$(RESET)"

test1: run_test_basic
test2: run_test_edge_cases
test3: run_test_fragmentation
test4: run_test_alignment
test5: run_test_multithread

re: fclean all

.PHONY: all clean fclean re test
