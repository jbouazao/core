/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 17:45:31 by oelbelam          #+#    #+#             */
/*   Updated: 2020/03/11 13:48:14 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		st_check_arg(uint8_t c, t_op_arg *args)
{
	int error;

	error = 1;
	if (((c >> 6) & 0b11) == REG_CODE && (args->sz_arg1 += 1))
		args->arg1 = 1;
	else
		error = 0;
	if ((((c >> 4) & 0b0011) == REG_CODE))
		args->arg2 = 1 + 0 * args->sz_arg2++;
	else if (((c >> 4) & 0b0011) == IND_CODE && (args->sz_arg2 += 2))
		args->arg2 = 3;
	else
		error = 0;
	if (((c >> 2) & 0b000011) == REG_CODE || ((c >> 2) & 0b000011) == IND_CODE
	|| ((c >> 2) & 0b000011) == DIR_CODE)
		error = 0;
	return (error);
}

int		st_execute(t_vm	*vm, t_proc **prcs)
{
	int32_t		tmp_r;
	short		ind_v;
	int			crt_p;
	int			y;
	
	crt_p = 0;
	tmp_r = 0;
	ind_v = 0;
	y = 1;
	if ((*prcs)->args.arg1 == 1)
	{
		if (vm->arena[((*prcs)->cur_pos) % MEM_SIZE] >= 1 &&
		vm->arena[((*prcs)->cur_pos) % MEM_SIZE] <= 16)
			tmp_r = (*prcs)->r[vm->arena[((*prcs)->cur_pos) % MEM_SIZE] - 1];
		else
			return ((*prcs)->args.sz_arg1 + (*prcs)->args.sz_arg2);
	}
	crt_p++;
	if ((*prcs)->args.arg2 == 1)
	{
		if (vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] >= 1 &&
		vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] <= 16)
			(*prcs)->r[vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] - 1] = tmp_r;
		else
			return ((*prcs)->args.sz_arg1 + (*prcs)->args.sz_arg2);
	}
	else if ((*prcs)->args.arg2 == 3)
	{
		int k = 0;
		ind_v = (vm->arena[(*prcs)->cur_pos + crt_p] << 8) | ((vm->arena[((*prcs)->cur_pos + crt_p + 1) % MEM_SIZE]));
		// ft_printf("%x\n", vm->arena[(*prcs)->cur_pos + crt_p]);
		// ft_printf("%x\n", vm->arena[(*prcs)->cur_pos + 1 + crt_p]);
		// ind_v *= (ind_v < 0 && (y = -1)) ? -1 : 1;
		// ft_printf("ind_v %d\n", ind_v);
		ind_v = (((ind_v % IDX_MOD)) + MEM_SIZE) % MEM_SIZE;
		vm->arena[((*prcs)->cur_pos - 2 + (ind_v)) % 4096] = (tmp_r & 0b11111111000000000000000000000000) >> 24;
		vm->arena[((*prcs)->cur_pos - 2 + (ind_v) + 1) % 4096] = (tmp_r & 0b00000000111111110000000000000000) >> 16;
		vm->arena[((*prcs)->cur_pos - 2 + (ind_v) + 2) % 4096] = (tmp_r & 0b00000000000000001111111100000000) >> 8;
		vm->arena[((*prcs)->cur_pos - 2 + (ind_v) + 3) % 4096] = tmp_r & 0b00000000000000000000000011111111;
		vm->ar_clr[((*prcs)->cur_pos - 2 + (ind_v)) % 4096] = (*prcs)->proc_clr;
		vm->ar_clr[((*prcs)->cur_pos - 2 + (ind_v) + 1) % 4096] = (*prcs)->proc_clr;
		vm->ar_clr[((*prcs)->cur_pos - 2 + (ind_v) + 2) % 4096] = (*prcs)->proc_clr;
		vm->ar_clr[((*prcs)->cur_pos - 2 + (ind_v) + 3) % 4096] = (*prcs)->proc_clr;
	}
	return ((*prcs)->args.sz_arg1 + (*prcs)->args.sz_arg2);
}

int	st_op(t_vm *vm, t_proc **prcs)
{
	int		arg_ret;

	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	if (!st_check_arg(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = ((skip_bytes(vm->arena[(*prcs)->cur_pos], 4, 2) +
		(*prcs)->cur_pos)) % MEM_SIZE;
	}
	else
	{
		ft_printf("||arg1 %d|arg2 %d|arg3 %d\n", (*prcs)->args.arg1, (*prcs)->args.arg2, (*prcs)->args.arg3);
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
		(*prcs)->cur_pos = ((*prcs)->cur_pos + st_execute(vm, prcs)) % MEM_SIZE;
				ft_printf("ST register 1 %d\n", (*prcs)->r[0]);
		ft_printf("ST register 2 %d\n", (*prcs)->r[1]);
	}
	return (1);
}