/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 17:51:21 by oelbelam          #+#    #+#             */
/*   Updated: 2020/06/18 17:21:13 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ld_check_arg(uint8_t c, t_op_arg *args)
{
	int error;

	error = 1;
	if (((c >> 6) & 0b11) == DIR_CODE && (args->sz_arg1 += 4))
		args->arg1 = 2;
	else if ((((c >> 6) & 0b11) == IND_CODE) && (args->sz_arg1 += 2))
		args->arg1 = 3;
	else
		error = 0;
	if ((((c >> 4) & 0b0011) == REG_CODE))
	{
		args->arg2 = 1 + 0 * args->sz_arg2++;
	}
	else
		error = 0;
	// if (((c >> 2) & 0b000011) == REG_CODE || ((c >> 2) & 0b000011) == IND_CODE
	// || ((c >> 2) & 0b000011) == DIR_CODE)
	// 	error = 0;
	return (error);
}

int		skip_bytes(uint8_t c, int size_dir, int num_args)
{
	int		bytes;

	bytes = 0;
	bytes += (((c >> 6) & 0b11) == REG_CODE) ? 1 : 0;
	bytes += (((c >> 6) & 0b11) == DIR_CODE) ? size_dir : 0;
	bytes += (((c >> 6) & 0b11) == IND_CODE) ? 2 : 0;
	if (num_args >= 2)
	{
		bytes += (((c >> 4) & 0b0011) == REG_CODE) ? 1 : 0;
		bytes += (((c >> 4) & 0b0011) == DIR_CODE) ? size_dir : 0;
		bytes += (((c >> 4) & 0b0011) == IND_CODE) ? 2 : 0;
	}
	if (num_args == 3)
	{
		bytes += (((c >> 2) & 0b000011) == REG_CODE) ? 1 : 0;
		bytes += (((c >> 2) & 0b000011) == DIR_CODE) ? size_dir : 0;
		bytes += (((c >> 2) & 0b000011) == IND_CODE) ? 2 : 0;
	}
	return (bytes + 1);
}

int		ld_execute(t_vm	*vm, t_proc **prcs)
{
	int16_t		_1param;
	short		tmp_idx;
	int			crt_p;
	int32_t		tmp_r2;
	

	tmp_idx = 0;
	crt_p = 0;
	if ((*prcs)->args.arg1 == DIR_CODE && (crt_p = 4))
	{
		tmp_r2 = vm->arena[(*prcs)->cur_pos] << 24 | vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE] << 16 | vm->arena[((*prcs)->cur_pos + 2) % MEM_SIZE] << 8 | vm->arena[((*prcs)->cur_pos + 3) % MEM_SIZE];
			// ft_printf("4a %d\n", tmp_r2);
	}
	else if ((*prcs)->args.arg1 == IND_CODE && (crt_p = 2))
	{
		tmp_idx = (vm->arena[(*prcs)->cur_pos] << 8) | ((vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE]));
		tmp_idx = ((*prcs)->cur_pos - 2 + ((tmp_idx % IDX_MOD)) + MEM_SIZE) % MEM_SIZE;
		// ft_printf("3a %d\n", tmp_idx);
		tmp_r2 = vm->arena[tmp_idx] << 24 | vm->arena[(tmp_idx + 1) % 4096] << 16 | vm->arena[(tmp_idx + 2) % 4096] << 8 | vm->arena[(tmp_idx + 3) % 4096];
	}
	if (vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] >= 1 &&
		vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] <= 16)
		{
			(*prcs)->r[vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] - 1] = tmp_r2;
			(*prcs)->carry = (tmp_r2 == 0) ? 1 : 0;
			// ft_printf("3afaaak %d\n", tmp_r2);
		}
	return (crt_p + 1);
}

int		ld_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	int		arg_ret;

	(void)head;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	if (!ld_check_arg(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = ((skip_bytes(vm->arena[(*prcs)->cur_pos], 4, 2) +
		(*prcs)->cur_pos)) % MEM_SIZE;
	}
	else
	{
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
		(*prcs)->cur_pos = ((*prcs)->cur_pos + ld_execute(vm, prcs)) % MEM_SIZE;
	}
	return (1);
}