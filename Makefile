NAME = corewar

SRCS =	srcs/main.c\
		srcs/parse_file.c\
		srcs/print_errors.c\
		srcs/read_bits.c\
		srcs/init_vm.c\
		srcs/set_vm_code.c\
		srcs/proces.c\
		srcs/live_op.c\
		srcs/exec_code.c\
		srcs/visu.c\
		srcs/ld_op.c\
		srcs/st_op.c\
		srcs/add_op.c\
		srcs/sub_op.c\
		srcs/and_op.c

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft

FT_PRINTF = ./ft_printf

FT_PRINTF_LIB = ./ft_printf/libftprintf.a

FLGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBFT) all
	make -C $(FT_PRINTF) all
	gcc -o $(NAME) $(FLGS) $(OBJS) $(FT_PRINTF_LIB) -lncurses

$(OBJ): %.o:%.c corewar.h
	gcc -c $(FLGS) $< -o $@

clean: 
	rm -rf $(OBJS)
	make -C $(LIBFT) clean
	make -C $(FT_PRINTF) clean

fclean : clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean
	make -C $(FT_PRINTF) fclean

re : fclean all
