/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:28:25 by oelbelam          #+#    #+#             */
/*   Updated: 2020/03/22 14:28:27 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_proc	*dup_prcs(t_proc *prcs, int16_t dir)
{
	t_proc *new;
	int	k;

	k = -1;
	new = (t_proc*)ft_memalloc(sizeof(t_proc));
	new->args = (t_op_arg){0,0,0,0,0,0};
	while (++k < 16)
		new->r[k] = prcs->r[k];
	new->cur_pos = dir;
	new->cycle_to_wait = 0;
	new->proc_clr = prcs->proc_clr;
	new->flag = 0;
	new->carry = prcs->carry;
	new->next = NULL;
	new->prev = NULL;
	return(new);
}

t_proc	*execute_lfork(t_vm *vm, t_proc **prcs)
{
	int16_t dir;
	t_proc	*new;

	dir = vm->arena[(*prcs)->cur_pos] << 8 | vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE];
	dir = ((*prcs)->cur_pos - 1 + dir + MEM_SIZE) % MEM_SIZE;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 2) % MEM_SIZE;
	new = dup_prcs(*prcs, dir);
	return (new);
}

int lfork_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	t_proc	*new;
	int16_t	dir;

	dir = 0;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	new = execute_lfork(vm, prcs);
	new->next = *head;
	(*head)->prev = new;
	*head = new;
	return (1);
}