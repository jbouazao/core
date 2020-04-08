/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:28:00 by oelbelam          #+#    #+#             */
/*   Updated: 2020/04/07 18:43:21 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		lldi_check_arg(uint8_t c, t_op_arg *args)
{
	int error;

	error = 1;
	if (((c >> 6) & 0b11) == DIR_CODE && (args->sz_arg1 += 2))
		args->arg1 = 2;
	else if ((((c >> 6) & 0b11) == IND_CODE) && (args->sz_arg1 += 2))
		args->arg1 = 3;
	else if ((((c >> 6) & 0b11) == REG_CODE) && (args->sz_arg1 += 1))
		args->arg1 = 1;
	else
		error = 0;
	if ((((c >> 4) & 0b0011) == REG_CODE))
		args->arg2 = 1 + 0 * args->sz_arg2++;
	else if ((((c >> 4) & 0b0011) == DIR_CODE) && (args->sz_arg2 += 2))
		args->arg2 = 2;
	else
		error = 0;
	if ((((c >> 2) & 0b000011) == REG_CODE))
		args->arg3 = 1 + 0 * args->sz_arg3++;
	else
		error = 0;
	return (error);
}

int		lldi_execute(t_vm *vm, t_proc **prcs)
{
	int		crt_p;
	int32_t tmp_r;
	int16_t	tmp_idx;
	int32_t	tmp_idx2;

	crt_p = 0;
	tmp_idx = 0;
	tmp_idx2 = 0;
	tmp_r = 0;
	if ((*prcs)->args.arg1 == REG_CODE && (crt_p += 1))
	{
		if (vm->arena[((*prcs)->cur_pos) % MEM_SIZE] >= 1 &&
		vm->arena[((*prcs)->cur_pos) % MEM_SIZE] <= 16)
			tmp_idx2 = (*prcs)->r[vm->arena[(*prcs)->cur_pos] - 1];
		else
			return ((*prcs)->args.sz_arg1 + (*prcs)->args.sz_arg2 + (*prcs)->args.sz_arg3);
	}
	else if ((*prcs)->args.arg1 == DIR_CODE && (crt_p += 2))
	{
		tmp_idx = vm->arena[((*prcs)->cur_pos) % MEM_SIZE] << 8 | vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE];
	}
	else if ((*prcs)->args.arg1 == IND_CODE && (crt_p += 2))
	{
		tmp_idx = (vm->arena[(*prcs)->cur_pos] << 8) | ((vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE]));
		tmp_idx = ((*prcs)->cur_pos - 2 + (tmp_idx % IDX_MOD) + MEM_SIZE) % MEM_SIZE; // tmp_idx + MEM_SIZE
		tmp_idx2 = vm->arena[tmp_idx] << 24 | vm->arena[(tmp_idx + 1) % MEM_SIZE] << 16 | vm->arena[(tmp_idx + 2) % MEM_SIZE] << 8 | vm->arena[(tmp_idx + 3) % MEM_SIZE];
		tmp_idx = 0;
	}
	if ((*prcs)->args.arg2 == REG_CODE)
	{
		// ft_printf("res: %x\n", tmp_idx + tmp_idx2 + (*prcs)->r[vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] - 1]);
		tmp_idx2 = tmp_idx + tmp_idx2 + (*prcs)->r[vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] - 1];
		crt_p += 1;
	}
	else if ((*prcs)->args.arg2 == DIR_CODE)
	{
		// ft_printf("arena %x\n", (vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] << 8 | vm->arena[((*prcs)->cur_pos + crt_p + 1) % MEM_SIZE]));
		tmp_idx += (vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] << 8 | vm->arena[((*prcs)->cur_pos + crt_p + 1) % MEM_SIZE]);
		// ft_printf("tmp_idx1 %d\n", tmp_idx);
		tmp_idx2 = (tmp_idx + tmp_idx2) % MEM_SIZE;
		crt_p += 2;
	}
	if (vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] >= 1 &&
		vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] <= 16)
	{
		(*prcs)->r[vm->arena[(*prcs)->cur_pos + crt_p] - 1] = vm->arena[((*prcs)->cur_pos - 2 + tmp_idx2 + MEM_SIZE) % MEM_SIZE] << 24 | vm->arena[((*prcs)->cur_pos - 2 + 1 + tmp_idx2 + MEM_SIZE) % MEM_SIZE] << 16 | vm->arena[((*prcs)->cur_pos - 2 + 2 + tmp_idx2 + MEM_SIZE) % MEM_SIZE] << 8 | vm->arena[((*prcs)->cur_pos - 2 + 3 + tmp_idx2 + MEM_SIZE) % MEM_SIZE];
		(*prcs)->carry = ((*prcs)->r[vm->arena[(*prcs)->cur_pos + crt_p] - 1] == 0) ? 1 : 0;
	}
	return (crt_p + 1);
}

int 	lldi_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	(void)head;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	if (!lldi_check_arg(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = ((skip_bytes(vm->arena[(*prcs)->cur_pos], 4, 2) +
		(*prcs)->cur_pos)) % MEM_SIZE;
	}
	else
	{
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
		(*prcs)->cur_pos = ((*prcs)->cur_pos + lldi_execute(vm, prcs)) % MEM_SIZE;
	}
	return (1);
}