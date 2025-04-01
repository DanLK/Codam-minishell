NAME = parser
SRC = 
MAIN = parser_main.c
SRC_DIR = ./src
OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(MAIN:%.c=$(OBJ_DIR)/%.o)

CFLAGS += -Wall -Wextra -Werror

LIBFT_NAME = ../libft/libft.a
LIBFT_PATH = ../libft

LEXER_PATH = ../lexer

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_NAME) $(MAIN_OBJ)
	$(CC) -Iinclude -I$(LEXER_PATH)/include -I$(LIBFT_PATH) -o $(NAME) $(CFLAGS) $(OBJ) $(MAIN_OBJ) $(LIBFT_NAME)

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