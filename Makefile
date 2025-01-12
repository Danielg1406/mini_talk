CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = 42_libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_DIR = printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

HEADER_DIR = .
HEADER = mini_talk.h

SRC_SERVER = server.c utils.c
SRC_CLIENT = client.c utils.c

OBJ_SERVER = $(SRC_SERVER:%.c=%.o)
OBJ_CLIENT = $(SRC_CLIENT:%.c=%.o)

RM = rm -f

all: submodules server client

submodules:
	@git submodule update --init --recursive $(LIBFT_DIR)
	@git submodule update --init --recursive $(PRINTF_DIR)

server: $(OBJ_SERVER) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -o server $(OBJ_SERVER) $(LIBFT) $(PRINTF)

client: $(OBJ_CLIENT) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -o client $(OBJ_CLIENT) $(LIBFT) $(PRINTF)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

clean:
	$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	$(RM) server client
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re submodules
