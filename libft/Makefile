NAME = libft.a
SOURCES = ft_atoi_base.c \
			ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memset.c \
			ft_memmove.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_atoi.c \
			ft_itoa.c \
			ft_split.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			printf/ft_printf.c \
			printf/ft_printc.c \
			printf/ft_prints.c \
			printf/ft_printp.c \
			printf/ft_printd.c \
			printf/ft_printu.c \
			printf/ft_printx.c \
			printf/ft_print_percent.c \
			gnl/get_next_line_bonus.c \
			gnl/get_next_line_utils_bonus.c
BONUS_SRCS = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c
OBJ_DIR = ./obj
OBJFILES = $(SOURCES:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)
CFLAGS += -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJFILES)
	ar rcs $(NAME) $(OBJFILES)

$(OBJ_DIR)/%.o: %.c 
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

bonus: $(OBJFILES) $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS) $(OBJFILES)

clean: 
	rm -f $(OBJFILES)
	rm -f $(BONUS_OBJS)
	rm -r -f $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus