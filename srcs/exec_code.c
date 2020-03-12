/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 15:09:37 by oelbelam          #+#    #+#             */
/*   Updated: 2020/03/12 12:13:31 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

const	t_ops	g_ops =
{
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
	{ 11, 6, 6, 11, 11, 7, 7, 7, 21, 26, 26, 801, 11, 51, 1001, 3},
	{ &live_op, &ld_op, &st_op, &add_op, &sub_op, &and_op, &or_op, &xor_op,
		&zjmp_op, &ldi_op, &sti_op, &fork_op, &lld_op, &lldi_op, &lfork_op,
		&aff_op}
};

t_ops	get_ops(void)
{
	return (g_ops);
}


int     get_op(t_vm *vm, t_proc **prc)
{
	uint8_t     op;
	t_ops		ops;

	op = vm->arena[(*prc)->cur_pos % MEM_SIZE];
	ops = get_ops();
	if (op >= 1 && op <= 16)
	{
		(*prc)->cycle_to_wait = ops.ctw[op - 1];
		(*prc)->current_op = ops.op_tab[op - 1];
		return (1);
	}
	else
		return (0);	
}