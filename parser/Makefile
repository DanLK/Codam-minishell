NAME = parser
SRC = tree.c memory_clears_parser.c parser.c parser_utilities.c parser_nodes.c debug.c tredirs_utils.c
MAIN = main_parser.c
LEXER_SRC = lexer.c lexer_utils.c lexer_utils_2.c token_list.c token_list_utils.c token_identifier.c readers.c initial_checks.c clear_list.c
SRC_DIR = ./src
OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(MAIN:%.c=$(OBJ_DIR)/%.o)
LEXER_OBJ = $(LEXER_SRC:%.c=$(LEXER_DIR)/obj/%.o)

CFLAGS += -Wall -Wextra -Werror

EXEC_SRC = error_msgs.c builtins_extra2.c builtins_extra.c builtins.c child_process.c external_commands.c readline.c signal_handling_extra.c signal_handling.c utils.c vars.c 
EXEC_OBJ = $(EXEC_SRC:%.c=$(EXEC_DIR)/obj/%.o)

LEXER_DIR = ../lexer
EXEC_DIR = ../execution

LIBFT_NAME = ../libft/libft.a
LIBFT_PATH = ../libft

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_NAME) $(MAIN_OBJ) $(LEXER_OBJ)
	$(CC) -Iinclude  -I$(LEXER_DIR)/include  -I$(LIBFT_PATH) -o $(NAME) $(CFLAGS) $(OBJ) $(MAIN_OBJ) $(LEXER_OBJ) $(LIBFT_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -c -Iinclude -I$(LEXER_DIR)/include -I$(LIBFT_PATH) $(CFLAGS) -o $@ $<

$(EXEC_DIR)/obj/%.o: $(EXEC_DIR)/sources/%.c
	mkdir -p $(dir $@)
	$(CC) -c -I$(EXEC_DIR)/includes -I$(PARSER_DIR)/include -I$(LEXER_DIR)/include \
	-I$(LIBFT_DIR) $(CFLAGS) -o $@ $<

$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_PATH)

$(LEXER_OBJ):
	$(MAKE) -C $(LEXER_DIR)

clean:
	rm -f $(OBJ)
	rm -f $(MAIN_OBJ)
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LEXER_DIR) clean
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LEXER_DIR) fclean
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re