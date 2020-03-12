#ifndef COREWAR_H
# define COREWAR_H
# include "../ft_printf/src/ft_printf.h"
# include "op.h"
# include <ncurses.h>

/*
** Error_numbers
*/

# define ERROR_OPEN				-8
# define ERROR_READING			-7
# define ERROR_MAGIC			-1
# define ERROR_NULL_NUMBER		-2
# define ERROR_NAME_LEN			-3
# define ERROR_CODE_SIZE		-4
# define ERROR_CHAMP_COMMENT	-5
# define ERROR_CODE_EXEC	 	-6
/*
**
*/


typedef struct	s_player
{
	char			*file_name;
	unsigned char	champion_name[128];
	uint32_t		exec_code_size;
	unsigned char	champion_comment[2048];
	unsigned char	*exec_code;
	int				pid;
}				t_player;

typedef struct s_op_arg
{
	uint8_t arg1;
	uint8_t sz_arg1;
	uint8_t arg2;
	uint8_t sz_arg2;
	uint8_t arg3;
	uint8_t sz_arg3;
}				t_op_arg;



typedef struct	s_vm
{
	int			nbr_of_args;
	uint8_t		arena[4096];
	int			ar_clr[4096];
	int			win_id; //initialize with the highest pid
	int			cycles;
	int			lv_bf_c_todie;
	int			c_to_die;
	int			nbr_chks;
	int			nbr_lives;
	t_player	*players;

}				t_vm;

typedef struct s_proc
{
	uint8_t			current_op;
	int32_t			r[REG_NUMBER];
	t_op_arg		args;
	int				next_step;
	int				cycle_to_wait;
	int				cur_pos;
	int				carry;
	int				flag;
	int				proc_clr;
	struct s_proc	*next;
}				t_proc;

typedef struct		s_ops
{
	char		op_tab[16];
	int			ctw[16];
	int			(*ops[16])(struct s_vm *vm, struct s_proc **procs);
}					t_ops;

typedef struct s_window
{
	WINDOW		*win;
	WINDOW		*menuwin;
}				t_window;


uint32_t	read_chk_bytes(int fd);
uint32_t	void_to_int(unsigned char *str);
int			parse_file(t_player *player);
void    	init_vm(t_vm *vm);
void	init_procs(t_vm *vm, t_player *player, t_proc **prcs);

void		print_errors(int error_num, t_player player);
void    	set_exec_code(t_vm *vm, t_player *player);

void		ft_init_player(t_player *p);
int			sti_check_params(unsigned char c, t_op_arg *sti_arg);
void		ft_init_args(t_op_arg *args);
int     	get_op(t_vm *vm, t_proc **prc);
int32_t		u_to_int(uint8_t *arena, int idx, int size);

t_ops	get_ops(void);

void	init_args(t_op_arg *args);

/*
** ops_ft
*/
int			skip_bytes(uint8_t c, int size_dir, int num_args);
int			live_op(t_vm *vm, t_proc **proc);
int			ld_op(t_vm *vm, t_proc **prcs);
int			st_op(t_vm *vm, t_proc **prcs);
int			add_op(t_vm *vm, t_proc **prcs);
int			sub_op(t_vm *vm, t_proc **prcs);
int			and_op(t_vm *vm, t_proc **prcs);
int			or_op(t_vm *vm, t_proc **prcs);
int			xor_op(t_vm *vm, t_proc **prcs);
int			zjmp_op(t_vm *vm, t_proc **prcs);
int			ldi_op(t_vm *vm, t_proc **prcs);
int			sti_op(t_vm *vm, t_proc **prcs);
int			fork_op(t_vm *vm, t_proc **prcs);
int			lld_op(t_vm *vm, t_proc **prcs);
int			lldi_op(t_vm *vm, t_proc **prcs);
int			lfork_op(t_vm *vm, t_proc **prcs);
int			aff_op(t_vm *vm, t_proc **prcs);


/*
**	visu
*/
void		visu(t_vm *vm, t_proc *proc);

#endif