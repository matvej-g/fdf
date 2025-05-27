NAME	:= fdf
CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code
#DFLAGS	:= -fsanitize=address -g
LIBMLX	:= ./libs/MLX42
LIBLIBFT := ./libft
HEADERS	:= -I $(LIBMLX)/include/MLX42 -I ./get_next_line
LIBS	:= $(LIBLIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	:= \
	./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c \
	fdf.c get_map_data.c map_utils.c draw_line_algo.c draw_utils.c error.c

OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		mkdir -p libs && \
		git clone --depth 1 --branch v2.3.3 https://github.com/codam-coding-college/MLX42 $(LIBMLX) && \
		cmake -S $(LIBMLX) -B $(LIBMLX)/build && \
		make -C $(LIBMLX)/build -j4; \
	fi

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBLIBFT)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	$(MAKE) -C $(LIBLIBFT) clean
	@rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBLIBFT) fclean
	@rm -rf libs
	@rm -rf $(NAME)

# deb : CFLAGS += $(DFLAGS)
# deb : clean $(OBJS)
# 	$(MAKE) -C $(LIBLIBFT)
# 	$(CC) $(OBJS) $(LIBS) $(HEADERS) $(DFLAGS) -o deb
# 	@printf "debug version ready.\n"

re: clean all

.PHONY: all, clean, fclean, re, libmlx