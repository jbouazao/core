#include "corewar.h"


void init_player(t_player *player)
{
	player->file_name = NULL;
	player->exec_code = NULL;
}

int main (int ac, char **av)
{
	t_player player[4];
	int i;

	i = 0;
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
	set_exec_code(&vm, player);
	t_proc		*prcs;
	t_proc		*it_prcs;
	t_ops		ops = get_ops();

	prcs = NULL;
	int flag = 0;
	i = 1;
	// while (i < 4097)
	// {
	// 	ft_printf("%02x ", vm.arena[i - 1]);
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
		// if (flag == 1 && cycles % c_to_die == 0)
		//     check_ft();
		it_prcs = prcs;
		while (it_prcs)
		{
			if (it_prcs->flag == 0)
			{
				if (!get_op(&vm, &it_prcs))
					it_prcs->cur_pos = (it_prcs->cur_pos + 1) % MEM_SIZE;
				else
					it_prcs->flag = 1;
			}
			if ((it_prcs->cycle_to_wait -= 1) && (it_prcs->cycle_to_wait) == 1)
			{
				ft_printf("Cycle %d\n", vm.cycles);
				ops.ops[it_prcs->current_op](&vm, &it_prcs);
				it_prcs->flag = 0;
				// i = 1;
			}
			// i = (i + 1) % MEM_SIZE;
			visu(&vm, prcs);
			// it_prcs->cur_pos = (it_prcs->cur_pos + 1) % MEM_SIZE;
			it_prcs = it_prcs->next;
		}
		if (flag == 2)
			return(0);
	}
	//  ft_printf("NUM OF ARGS = %d\n", vm.nbr_of_args);
	// while (prcs)
	// {
	//     ft_printf("POS %d | R1 -> %d\n", prcs->cur_pos, prcs->r[0]);
	//     prcs = prcs->next;
	// }

}