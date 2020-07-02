/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:26:20 by oelbelam          #+#    #+#             */
/*   Updated: 2020/06/18 15:23:22 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		sti_check_arg(uint8_t c, t_op_arg *args)
{
	int error;

	error = 1;
	if ((((c >> 6) & 0b11) == REG_CODE) && (args->sz_arg1 += 1))
		args->arg1 = 1;
	else
		error = 0;
	if ((((c >> 4) & 0b0011) == REG_CODE))
		args->arg2 = 1 + 0 * args->sz_arg2++;
	else if ((((c >> 4) & 0b0011) == DIR_CODE) && (args->sz_arg2 += 2))
		args->arg2 = 2;
	else if ((((c >> 4) & 0b0011) == IND_CODE) && (args->sz_arg2 += 2))
		args->arg2 = 3;
	else
		error = 0;
	if ((((c >> 2) & 0b000011) == REG_CODE))
		args->arg3 = 1 + 0 * args->sz_arg3++;
	else if ((((c >> 2) & 0b000011) == DIR_CODE) && (args->sz_arg3 += 2))
		args->arg3 = 2;
	else
		error = 0;
	return (error);
}

int		sti_execute(t_vm *vm, t_proc **prcs)
{
	int		crt_p;
	int32_t tmp_r;
	int16_t tmp_idx;
	int32_t	tmp_idx2;

	crt_p = 0;
	tmp_idx = 0;
	tmp_idx2 = 0;
	tmp_r = 0;
	if ((*prcs)->args.arg2 == REG_CODE && (crt_p += 1))
	{
		if (vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE] >= 1 &&
		vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE] <= 16)
			tmp_idx2 = (*prcs)->r[vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE] - 1];
		else
			return ((*prcs)->args.sz_arg1 + (*prcs)->args.sz_arg2 + (*prcs)->args.sz_arg3);
	}
	else if ((*prcs)->args.arg2 == DIR_CODE && (crt_p += 2))
		tmp_idx = vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE] << 8 | vm->arena[((*prcs)->cur_pos + 2) % MEM_SIZE] % MEM_SIZE;
	else if ((*prcs)->args.arg2 == IND_CODE && (crt_p += 2))
	{
		tmp_idx = (vm->arena[(*prcs)->cur_pos + 1] << 8) | ((vm->arena[((*prcs)->cur_pos + 2) % MEM_SIZE]));
		tmp_idx = ((*prcs)->cur_pos - 2 + ((tmp_idx % IDX_MOD)) + MEM_SIZE) % MEM_SIZE;
		tmp_idx2 = vm->arena[tmp_idx] << 24 | vm->arena[(tmp_idx + 1) % MEM_SIZE] << 16 | vm->arena[(tmp_idx + 2) % MEM_SIZE] << 8 | vm->arena[(tmp_idx + 3) % MEM_SIZE];
		tmp_idx = 0;
	}
	if ((*prcs)->args.arg3 == REG_CODE)
	{
		if (vm->arena[((*prcs)->cur_pos + 1 + crt_p) % MEM_SIZE] >= 1 &&
		vm->arena[((*prcs)->cur_pos + 1 + crt_p) % MEM_SIZE] <= 16)
		{
			tmp_idx2 = (tmp_idx + tmp_idx2 + (*prcs)->r[vm->arena[((*prcs)->cur_pos + 1 + crt_p) % MEM_SIZE] - 1]) % MEM_SIZE;
			tmp_idx2 = ((*prcs)->cur_pos - 2 + ((tmp_idx2 % IDX_MOD)) + MEM_SIZE) % MEM_SIZE;
		}
		else
			return ((*prcs)->args.sz_arg1 + (*prcs)->args.sz_arg2 + (*prcs)->args.sz_arg3);
		crt_p += 1;
	}
	else if ((*prcs)->args.arg3 == DIR_CODE)
	{
		tmp_idx = (tmp_idx + (vm->arena[((*prcs)->cur_pos + 1 + crt_p) % MEM_SIZE] << 8 | vm->arena[((*prcs)->cur_pos + 1 + crt_p + 1) % MEM_SIZE]));
		tmp_idx2 = tmp_idx + tmp_idx2;
		tmp_idx2 = ((*prcs)->cur_pos - 2 + ((tmp_idx2 % IDX_MOD)) + MEM_SIZE) % MEM_SIZE;
		crt_p += 2;
	}
	if (vm->arena[((*prcs)->cur_pos) % MEM_SIZE] >= 1 &&
		vm->arena[((*prcs)->cur_pos) % MEM_SIZE] <= 16)
	{
		tmp_r = (*prcs)->r[vm->arena[(*prcs)->cur_pos] - 1];
		vm->arena[tmp_idx2] = (tmp_r & 0b11111111000000000000000000000000) >> 24;
		vm->arena[(tmp_idx2 + 1) % MEM_SIZE] = (tmp_r & 0b00000000111111110000000000000000) >> 16;
		vm->arena[(tmp_idx2 + 2) % MEM_SIZE] = (tmp_r & 0b00000000000000001111111100000000) >> 8;
		vm->arena[(tmp_idx2 + 3) % MEM_SIZE] = (tmp_r & 0b00000000000000000000000011111111);;
		vm->ar_clr[tmp_idx2] = (*prcs)->proc_clr;
		vm->ar_clr[(tmp_idx2 + 1) % MEM_SIZE] = (*prcs)->proc_clr;
		vm->ar_clr[(tmp_idx2 + 2) % MEM_SIZE] = (*prcs)->proc_clr;
		vm->ar_clr[(tmp_idx2 + 3) % MEM_SIZE] = (*prcs)->proc_clr;
	}
	return (crt_p + 1);
}

int 	sti_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	(void)head;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	if (!sti_check_arg(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = ((skip_bytes(vm->arena[(*prcs)->cur_pos], 2, 3) +
		(*prcs)->cur_pos)) % MEM_SIZE;
	}
	else
	{
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
		(*prcs)->cur_pos = ((*prcs)->cur_pos + sti_execute(vm, prcs)) % MEM_SIZE;
	}
	return (1);
}
