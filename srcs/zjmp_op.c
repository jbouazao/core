/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:24:53 by oelbelam          #+#    #+#             */
/*   Updated: 2020/03/14 14:02:17 by oelbelam         ###   ########.fr       */
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
		ft_printf("test\n");
		jump = vm->arena[((*prcs)->cur_pos) % 4096] << 8 | vm->arena[((*prcs)->cur_pos + 1) % 4096];
		jump = jump % IDX_MOD;
		(*prcs)->cur_pos = (((*prcs)->cur_pos - 1 + jump) + MEM_SIZE) % MEM_SIZE;
		ft_printf("cur_pos: %d\n", (*prcs)->cur_pos);
	}
	else
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 2) % MEM_SIZE;
	return (1);
}