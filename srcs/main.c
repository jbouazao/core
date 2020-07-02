#include "corewar.h"


void init_player(t_player *player)
{
	player->file_name = NULL;
	player->exec_code = NULL;
	player->live = 0;
}

void    re_init_live(t_proc **proc)
{
    t_proc *it_proc;

    it_proc = *proc;
    while (it_proc)
    {
        it_proc->live = 0;
        it_proc = it_proc->next;
    }
}

int main (int ac, char **av)
{
	t_player *player;
	int i;

	i = 0;
	player = ft_memalloc(sizeof(t_player) * 4);
	while (i < ac - 1)
	{
		init_player(&player[i]);
		player[i].pid = i + 1;
		i++;
	}
	i = 1;
	int k = 0;
	while (i < ac)
	{
		player[k].file_name = av[i];
		k++;
		i++;
	}
	i = 0;
	// while (i < ac - 1)
	// 	ft_printf("%s ", player[i++].file_name);
	// ft_printf("\n");
	// parse start here
	i = 0;
	int error;
	while (i < ac - 1)
	{
		if ((error = parse_file(&player[i])) < 0)
		{
			print_errors(error, player[i]);
			return (0);
		}
		i++;
	}

	/*
	** This comment below is for rint every variable in player struct
	*/

	/*********************************************************************/

	// i = 0;
	// k = 0;
	// while (i < ac - 1)
	// {
	//     ft_printf("player = %s | c_name %s | Code_size %d | c_comment %s | Exec_code ", player[i].player, player[i].champion_name, player[i].exec_code_size, player[i].champion_comment);
	//     k = 0;
	//     while (k < player[i].exec_code_size)
	//     {
	//         ft_printf("%x", player[i].exec_code[k]);
	//         k++;
	//     }
	//     ft_printf("|\n\n");
	//     i++;
	// }

	/********************************************************************/
	t_vm    vm;
	vm.nbr_of_args = ac - 1;
	init_vm(&vm);
	vm.num_player = ac - 1;
	set_exec_code(&vm, player);
	t_proc		*prcs;
	t_proc		*it_prcs;
	int			dump;
	t_ops		ops = get_ops();

	prcs = NULL;
	int flag = 0;
	i = 1;
	// while (i < 4097)
	// {
	//8837 diyat l mouchkila
	dump = 10676;
	//dump = 400;
	// 	if ((i % 64) == 0 && i != 0)
	// 		ft_printf("\n");
	// 	i++;
	// }
	// i = 0;
	init_procs(&vm, player, &prcs);
	i = 1;
	while (1)
	{
		vm.cycles++;
		// ft_printf("Cycle %d\n", vm.cycles);
		// ft_printf("Cycle_to_di |%d|   \n", vm.c_to_die);
		// ft_printf("NBR_CHECKS |%d|    \n", vm.nbr_chks);
		if (vm.c_to_die >= 0 && ((vm.cycles % vm.c_to_die) == 0))
		{
			check_ft(&vm, &prcs);
            re_init_live(&prcs);
		}
		else if (vm.c_to_die < 0)
		{
			check_ft(&vm, &prcs);
            re_init_live(&prcs);			
		}
		it_prcs = prcs;
		// if ((vm.cycles % vm.c_to_die) == 0)
		// 	ft_printf("---> %p \n", prcs);
		if (!it_prcs)
			break;
		while (it_prcs)
		{
			if (it_prcs->flag == 0)
			{
				if (!get_op(&vm, &it_prcs))
				{
					it_prcs->cur_pos = (it_prcs->cur_pos + 1) % MEM_SIZE;
					it_prcs = it_prcs->next;
					continue;
				}
				else
					it_prcs->flag = 1;
			}
			if ((it_prcs->cycle_to_wait -= 1) && (it_prcs->cycle_to_wait) == 1)
			{
				ops.ops[it_prcs->current_op](&vm, &it_prcs, &prcs, &player);
				it_prcs->flag = 0;
				// i = 1;
			}
			// i = (i + 1) % MEM_SIZE;
			// it_prcs->cur_pos = (it_prcs->cur_pos + 1) % MEM_SIZE;
			it_prcs = it_prcs->next;
		}
		visu(&vm, prcs);
		// if (dump == vm.cycles)
		// {
		// 	short	it;
		// 	int p = 0 , l = 0;
		// 	it = 0;
		// 	it_prcs = prcs;
		// 	// while (it_prcs)
		// 	// {
		// 	// 	ft_printf("--------- Proc %d --------- \n ", p);
		// 	// 	ft_printf("current pos  %d \n ", it_prcs->cur_pos);
		// 	// 	ft_printf("current OP  %d \n ", it_prcs->current_op);
		// 	// 	l = 0;
		// 	// 	while (l < 16)
		// 	// 	{
		// 	// 		ft_printf("register_num[%d] = %d\n", l, it_prcs->r[l]);
		// 	// 		l++;
		// 	// 	}
		// 	// 	it_prcs = it_prcs->next;
		// 	// 	p++;
		// 	// }
		// 	ft_printf("0x0000 : ");
		// 	while (it < 4096)
		// 	{
		// 		// if (it != 0 && (it % 63) == 0)
		// 		// 	ft_printf("\n");
		// 		if (it != 0 && it % 64 == 0)
		// 			ft_printf("\n%#.4x : ", it);
		// 		ft_printf("%02x ", vm.arena[it]);
		// 		it++;
		// 	}
		// }
		// if (flag == 2)
		// 	return(0);
	}
	//  ft_printf("NUM OF ARGS = %d\n", vm.nbr_of_args);
	// while (prcs)
	// {
	//     ft_printf("POS %d | R1 -> %d\n", prcs->cur_pos, prcs->r[0]);
	//     prcs = prcs->next;
	// }
}