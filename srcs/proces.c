/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 13:45:20 by oelbelam          #+#    #+#             */
/*   Updated: 2020/04/11 00:59:56 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_proc	*init_proc(t_vm *vm, t_player player, t_proc **prcs)
{
	t_proc	*new;
	int		j;

	j = 1;
	new = (t_proc*)ft_memalloc(sizeof(t_proc));
	new->r[0] = player.pid * -1;
	while (j < 16)
		new->r[j++] = 0;
	new->cur_pos = (player.pid - 1) * (MEM_SIZE / vm->nbr_of_args);
	new->cycle_to_wait = 0;
	new->live = 0;
	new->flag = 0;
	new->carry = 0;
	new->current_op = -1;
	new->proc_clr = player.pid;
	new->next = NULL;
	return (new);
}

void	init_procs(t_vm *vm, t_player *player, t_proc **prcs)
{
	int i;
	int j;
	t_proc *tail;
	t_proc *it_prev;

	j = 1;
	i = vm->nbr_of_args - 1;
	while (i >= 0)
	{
		if (!*prcs)
		{
			*prcs = init_proc(vm, player[i], prcs);
			(*prcs)->prev = NULL;
		}
		else
		{
			tail = *prcs;
			it_prev = tail;
			while (tail->next)
			{
				it_prev = tail;
				tail = tail->next;
			}
			tail->next = init_proc(vm, player[i], prcs);
			tail->next->prev = tail;
		}
		i--;
	}
}