#include "corewar.h"

void    init_vm(t_vm *vm)
{
    int i;

    i = 0;
    while (i < 4096)
	{
        vm->arena[i] = 0;
		vm->ar_clr[i++] = 0;
	}
    vm->c_to_die = CYCLE_TO_DIE;
    vm->cycles = 0;
    vm->win_id = 0;
    vm->players = NULL;
    vm->nbr_chks = 0;
    vm->lv_bf_c_todie = 0;
}

void	init_args(t_op_arg *args)
{
	args->arg1 = 0;
	args->arg2 = 0;
	args->arg3 = 0;
	args->sz_arg1 = 0;
	args->sz_arg2 = 0;
	args->sz_arg3 = 0;
}