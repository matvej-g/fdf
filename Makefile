NAME	:= fdf
CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code
DFLAGS	:= -g
LIBMLX	:= ./libs/MLX42
LIBPRINTF := ./ft_printf
LIBLIBFT := ./libft
HEADERS	:= -I $(LIBMLX)/include/MLX42 -I $(LIBPRINTF) -I ./get_next_line
LIBS	:= $(LIBLIBFT)/libft.a $(LIBPRINTF)/libftprintf.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

#SRCS		:= get_map_data.c ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c

SRCS	:= draw_line_test.c

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
	$(MAKE) -C $(LIBPRINTF)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	$(MAKE) -C $(LIBPRINTF) clean
	$(MAKE) -C $(LIBLIBFT) clean
	@rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBPRINTF) fclean
	$(MAKE) -C $(LIBLIBFT) fclean
	@rm -rf libs
	@rm -rf $(NAME)

deb : CFLAGS += $(DFLAGS)
deb : clean $(OBJS)
	$(MAKE) -C $(LIBLIBFT)
	$(MAKE) -C $(LIBPRINTF)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o deb
	@printf "debug version ready.\n"

re: clean all

.PHONY: all, clean, fclean, re, libmlx, deb