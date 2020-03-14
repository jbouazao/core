/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:41:49 by jbouazao          #+#    #+#             */
/*   Updated: 2020/03/14 14:03:22 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		sub_check_arg(uint8_t c, t_op_arg *args)
{
	int error;

	error = 1;
	if (((c >> 6) & 0b11) == REG_CODE)
		args->arg1 = 1 + 0 * args->sz_arg1++;
	else
		error = 0;
	if ((((c >> 4) & 0b0011) == REG_CODE))
		args->arg2 = 1 + 0 * args->sz_arg2++;
	else
		error = 0;
	if ((((c >> 2) & 0b000011) == REG_CODE))
		args->arg3 = 1 + 0 * args->sz_arg3++;
	else
		error = 0;
	return (error);
}

static int		sub_execute(t_vm *vm, t_proc **prcs)
{
	if (vm->arena[((*prcs)->cur_pos) % MEM_SIZE] >= 1 &&
	vm->arena[((*prcs)->cur_pos) % MEM_SIZE] <= 16 &&
	vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE] >= 1 &&
	vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE] <= 16 &&
	vm->arena[((*prcs)->cur_pos + 2) % MEM_SIZE] >= 1 &&
	vm->arena[((*prcs)->cur_pos + 2) % MEM_SIZE] <= 16)
	{
		(*prcs)->r[vm->arena[((*prcs)->cur_pos + 2) % MEM_SIZE] - 1] =
		(*prcs)->r[vm->arena[(*prcs)->cur_pos] - 1] -
		(*prcs)->r[vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE] - 1];
		(*prcs)->carry = ((*prcs)->r[vm->arena[((*prcs)->cur_pos + 2) %
		MEM_SIZE] - 1] == 0) ? 1 : 0;
	}
	return (3);
}

int		sub_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	int		arg_ret;

	(void)head;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	if (!sub_check_arg(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = ((skip_bytes(vm->arena[(*prcs)->cur_pos], 4, 3) +
		(*prcs)->cur_pos)) % MEM_SIZE;
	}
	else
	{
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
		(*prcs)->cur_pos = ((*prcs)->cur_pos + sub_execute(vm, prcs)) % MEM_SIZE;
		ft_printf("LD register 1 %d\n", (*prcs)->r[0]);
		ft_printf("LD register 2 %d\n", (*prcs)->r[1]);
	}
	return (1);
}