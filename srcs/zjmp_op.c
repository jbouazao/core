/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myMac <myMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:24:53 by oelbelam          #+#    #+#             */
/*   Updated: 2020/07/05 18:57:05 by myMac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int zjmp_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	int16_t	jump;

	(void)head;
	jump = 0;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	if ((*prcs)->carry == 1)
	{
		jump = vm->arena[((*prcs)->cur_pos) % MEM_SIZE] << 8 | vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE];
		jump = jump % IDX_MOD;
		(*prcs)->cur_pos = (((*prcs)->cur_pos - 1 + jump) + MEM_SIZE) % MEM_SIZE;
	}
	else
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 2) % MEM_SIZE;
	return (1);
}