#include "corewar.h"

t_proc	*init_proc(t_vm *vm, t_player player, t_proc **prcs)
{
	t_proc	*new;
	int		j;

	j = 1;
	new = (t_proc*)ft_memalloc(sizeof(t_proc));
	ft_printf("PLYAER PID %d\n", player.pid);
	new->r[0] = player.pid * -1;
	while (j < 16)
		new->r[j++] = 0;
	new->cur_pos = (player.pid - 1) * (MEM_SIZE / vm->nbr_of_args);
	new->cycle_to_wait = 0;
	new->live = 0;
	new->flag = 0;
	new->carry = 0;
	new->proc_clr = player.pid;
	new->next = NULL;
	return (new);
}


void	init_procs(t_vm *vm, t_player *player, t_proc **prcs)
{
	int i;
	int j;
	t_proc *head;

	j = 1;
	i = vm->nbr_of_args - 1;
	while (i >= 0)
	{
		if (!*prcs)
			*prcs = init_proc(vm, player[i], prcs);
		else
		{
			head = *prcs;
			while (head->next)
				head = head->next;
			head->next = init_proc(vm, player[i], prcs);
		}
		i--;
	}
}