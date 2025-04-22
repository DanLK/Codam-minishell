NAME = minishell
MAIN = minishell.c
SRC =
SRC_DIR = ./src
OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(MAIN:%.c=$(OBJ_DIR)/%.o)

EXEC_SRC = builtins.c child_process.c external_commands.c readline.c signal_handling.c utils.c vars.c 
EXEC_OBJ = $(EXEC_SRC:%.c=$(EXEC_DIR)/obj/%.o)

CFLAGS += -Wall -Wextra -Werror

LIBFT_NAME = ../libft/libft.a
LIBFT_DIR = ../libft
EXEC_DIR = ../execution

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_NAME) $(MAIN_OBJ) $(EXEC_OBJ)
	$(CC) -I$(EXEC_DIR)/includes -I$(LIBFT_DIR) -o $(NAME) $(CFLAGS) $(OBJ) $(MAIN_OBJ) $(EXEC_OBJ) $(LIBFT_NAME) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -c -I$(EXEC_DIR)/includes -I$(LIBFT_DIR) $(CFLAGS) -o $@ $<

$(EXEC_DIR)/obj/%.o: $(EXEC_DIR)/sources/%.c
	mkdir -p $(dir $@)
	$(CC) -c -I$(EXEC_DIR)/includes -I$(LIBFT_DIR) $(CFLAGS) -o $@ $<

$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	rm -f $(MAIN_OBJ)
	rm -rf $(OBJ_DIR)
	rm -f $(EXEC_DIR)/$(EXEC_OBJ)
	rm -rf $(EXEC_DIR)/$(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

#cc execution/sources/*.c libft/*.c libft/printf/*.c -lreadline -o minishell