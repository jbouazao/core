/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 21:04:10 by oelbelam          #+#    #+#             */
/*   Updated: 2020/04/08 19:52:06 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	ft_delete_node(t_proc **prcs, int index, t_proc **tmp)
{
	t_proc	*it_prcs;
	t_proc	*to_del;
	int		i;

	i = -1;
	it_prcs = *prcs;
	while (++i < index)
		it_prcs = it_prcs->next;
	if (it_prcs->prev && it_prcs->next)
	{
		to_del = it_prcs;
		it_prcs->prev->next = it_prcs->next;
		it_prcs->next->prev = it_prcs->prev;
		it_prcs = it_prcs->prev->next;
		free(to_del);
		*tmp = it_prcs;
		return (2);
	}
	else if (!it_prcs->prev && it_prcs->next)
	{
		to_del = it_prcs;
        it_prcs = it_prcs->next;
        (*prcs) = (*prcs)->next;
        (*prcs)->prev = NULL;
        free(to_del);
        it_prcs->prev = NULL;
        *tmp = it_prcs;
        return (2);
	}
	else
	{
		if (it_prcs->prev)
		{
			to_del = it_prcs;
			it_prcs->prev->next = NULL;
			free(to_del);
            *tmp = it_prcs;
			return (1);
		}
		else
		{
			free(it_prcs);
			it_prcs = NULL;
			*prcs = NULL;
            *tmp = it_prcs;
			return (1);
		}
	}
}

int		check_ft(t_vm *vm, t_proc **prcs)
{
	t_proc *it_prcs;
	t_proc **temp_prcs;
	int		index;

	it_prcs = *prcs;
	index = 0;
	while (it_prcs)
	{
		if (it_prcs->live == 0)
		{
			temp_prcs = &it_prcs;
			if (it_prcs->prev != NULL)
			{
				if (ft_delete_node(prcs, index, &it_prcs) == 2)
					continue;
				else
					break;
			}
			else
			{
				if (ft_delete_node(prcs, index, &it_prcs) == 2)
					continue;
				else
					break;
			}
		}
		index += 1;
		it_prcs = it_prcs->next;
	}
	if (vm->nbr_lives >= 21 || vm->nbr_chks == 11)
	{
		vm->c_to_die = vm->c_to_die - CYCLE_DELTA;
		vm->nbr_lives = 0;
		vm->nbr_chks = 0;
	}
	else if (vm->nbr_chks <= 10)
	{
		vm->nbr_chks++;
		vm->nbr_lives = 0;
	}
	return (1);
}