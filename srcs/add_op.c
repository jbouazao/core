/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:06:04 by oelbelam          #+#    #+#             */
/*   Updated: 2020/03/14 14:00:08 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		add_check_arg(uint8_t c, t_op_arg *args)
{
	int error;

	error = 1;
	if (((c >> 6) & 0b11) == REG_CODE)
		args->arg1 = 1 + 0 * args->sz_arg1++;
	else
		error = 0;
	if (((c >> 4) & 0b0011) == REG_CODE)
		args->arg2 = 1 + 0 * args->sz_arg2++;
	else
		error = 0;
	if (((c >> 2) & 0b000011) == REG_CODE)
		args->arg3 = 1 + 0 * args->sz_arg3++;
	else
		error = 0;
	return (error);
}

int		add_execut(t_vm *vm, t_proc **prcs)
{
	int32_t		tmp_r;
	int			crt_p;

	crt_p = 0;
	tmp_r = 0;
	if (vm->arena[((*prcs)->cur_pos) % MEM_SIZE] >= 1 && vm->arena[((*prcs)->cur_pos) % MEM_SIZE] <= 16)
		tmp_r = (*prcs)->r[vm->arena[((*prcs)->cur_pos) % MEM_SIZE] - 1];
	else
		return ((*prcs)->args.sz_arg1 + (*prcs)->args.sz_arg1 + (*prcs)->args.sz_arg1);
	crt_p++;
	if (vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] >= 1 && vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] <= 16)
		tmp_r = tmp_r + (*prcs)->r[vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] - 1];
	else
		return ((*prcs)->args.sz_arg1 + (*prcs)->args.sz_arg1 + (*prcs)->args.sz_arg1);
	crt_p++;
	if (vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] >= 1 && vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] <= 16)
	{
		(*prcs)->r[vm->arena[((*prcs)->cur_pos + crt_p) % MEM_SIZE] - 1] = tmp_r;
		(*prcs)->carry = (tmp_r == 0) ? 1 : 0;
	}
	return ((*prcs)->args.sz_arg1 + (*prcs)->args.sz_arg1 + (*prcs)->args.sz_arg1);
}

int		add_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	int		arg_ret;

	(void)head;
	arg_ret = 0;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	if (!add_check_arg(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = ((skip_bytes(vm->arena[(*prcs)->cur_pos], 4, 3) +
		(*prcs)->cur_pos)) % MEM_SIZE;
	}
	else
	{
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
		(*prcs)->cur_pos = ((*prcs)->cur_pos + add_execut(vm, prcs)) % MEM_SIZE;
		ft_printf("ADD register 1 %d\n", (*prcs)->r[0]);
		ft_printf("ADD register 2 %d\n", (*prcs)->r[1]);
		ft_printf("ADD register 2 %d\n", (*prcs)->r[2]);
		ft_printf("ADD register 2 %d\n", (*prcs)->r[3]);
		ft_printf("ADD register 2 %d\n", (*prcs)->r[4]);
		ft_printf("ADD register 2 %d\n", (*prcs)->r[5]);
		ft_printf("ADD register 2 %d\n", (*prcs)->r[6]);
		ft_printf("ADD register 2 %d\n", (*prcs)->r[8]);
		ft_printf("ADD register 2 %d\n", (*prcs)->r[9]);
		ft_printf("ADD register 2 %d\n", (*prcs)->r[10]);
		ft_printf("ADD register 2 %d\n", (*prcs)->r[11]);
	}
	return (1);
}