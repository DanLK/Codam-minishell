NAME = lexer
SRC = lexer.c lexer_utils.c lexer_utils_2.c token_list.c token_list_utils.c token_identifier.c readers.c initial_checks.c clear_list.c
MAIN = main_lexer.c
SRC_DIR = ./src
OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(MAIN:%.c=$(OBJ_DIR)/%.o)

CFLAGS += -Wall -Wextra -Werror

LIBFT_NAME = ../libft/libft.a
LIBFT_PATH = ../libft

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_NAME) $(MAIN_OBJ)
	$(CC) -Iinclude -I$(LIBFT_PATH) -o $(NAME) $(CFLAGS) $(OBJ) $(MAIN_OBJ) $(LIBFT_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -c -Iinclude -I$(LIBFT_PATH) $(CFLAGS) -o $@ $<

$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	rm -f $(OBJ)
	rm -f $(MAIN_OBJ)
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
