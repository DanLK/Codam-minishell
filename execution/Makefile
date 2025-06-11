NAME = minishell
MAIN = main_execution.c
SRC = builtins_extra2.c builtins_extra.c builtins.c child_process.c external_commands.c readline.c signal_handling_extra.c signal_handling.c utils.c vars.c 
LEXER_SRC = lexer.c lexer_utils.c lexer_utils_2.c token_list.c token_list_utils.c token_identifier.c readers.c initial_checks.c clear_list.c
PARSER_SRC = tree.c memory_clears_parser.c parser.c parser_utilities.c parser_nodes.c debug.c tredirs_utils.c
TRAV_SRC = executioner.c var_expansion.c var_expansion_utils.c heredoc.c cmd_str_utilities.c redir_experiments.c redirections.c pipes.c
SRC_DIR = ./sources
OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(MAIN:%.c=$(OBJ_DIR)/%.o)
LEXER_OBJ = $(LEXER_SRC:%.c=$(LEXER_DIR)/obj/%.o)
PARSER_OBJ = $(PARSER_SRC:%.c=$(PARSER_DIR)/obj/%.o)
TRAV_OBJ = $(TRAV_SRC:%.c=$(TRAV_DIR)/obj/%.o)

CFLAGS += -Wall -Wextra -Werror

LIBFT_NAME = ../libft/libft.a
LIBFT_DIR = ../libft
TRAV_DIR = ../traversal
PARSER_DIR = ../parser
LEXER_DIR = ../lexer

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_NAME) $(MAIN_OBJ) $(EXEC_OBJ) $(PARSER_OBJ) $(LEXER_OBJ) $(TRAV_OBJ) 
	$(CC) -Iinclude -I$(EXEC_DIR)/includes -I$(LEXER_DIR)/include -I$(PARSER_DIR)/include \
	-I$(LIBFT_DIR) -o $(NAME) $(CFLAGS) $(OBJ) $(MAIN_OBJ) $(EXEC_OBJ) $(PARSER_OBJ) $(LEXER_OBJ) \
	$(TRAV_OBJ) $(LIBFT_NAME) -lreadline
#-L/opt/homebrew/opt/readline/lib 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -c -Iinclude -I$(EXEC_DIR)/includes -I$(PARSER_DIR)/include -I$(LEXER_DIR)/include \
	-I$(LIBFT_DIR) $(CFLAGS) -o $@ $<
#-I/opt/homebrew/opt/readline/include 

$(EXEC_DIR)/obj/%.o: $(EXEC_DIR)/sources/%.c
	mkdir -p $(dir $@)
	$(CC) -c -I$(EXEC_DIR)/includes -I$(LIBFT_DIR) $(CFLAGS) -o $@ $<

$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_DIR)

$(LEXER_OBJ):
	$(MAKE) -C $(LEXER_DIR)

$(PARSER_OBJ):
	$(MAKE) -C $(PARSER_DIR)

$(TRAV_OBJ):
	$(MAKE) -C $(TRAV_DIR)

clean:
	rm -f $(OBJ)
	rm -f $(MAIN_OBJ)
	rm -rf $(OBJ_DIR)
#	rm -f $(EXEC_DIR)/$(EXEC_OBJ)
#	rm -rf $(EXEC_DIR)/$(OBJ_DIR)
	rm -f .shell_history
	$(MAKE) -C $(LEXER_DIR) clean
	$(MAKE) -C $(PARSER_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LEXER_DIR) fclean
	$(MAKE) -C $(PARSER_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

#cc execution/sources/*.c libft/*.c libft/printf/*.c -lreadline -o minishell