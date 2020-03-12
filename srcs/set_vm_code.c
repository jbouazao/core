#include "corewar.h"

void    set_exec_code(t_vm *vm, t_player *player)
{
	int	position;
	int	i;
	int	k;

	i = 0;
	position = 0;
	while (i < vm->nbr_of_args)
	{
		position = (MEM_SIZE / vm->nbr_of_args) * i;
		k = 0;
		while (k < player[i].exec_code_size)
		{
			vm->arena[position + k] = player[i].exec_code[k];
			vm->ar_clr[position + k] = player[i].pid;
			k++;
		}
		i++;
	}
}
