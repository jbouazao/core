/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 21:04:10 by oelbelam          #+#    #+#             */
/*   Updated: 2020/03/22 17:57:33 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	ft_delete_node(t_proc **it_prcs, t_proc **temp_prcs)
{
	if ((*it_prcs)->prev && (*it_prcs)->next)
	{
		(*it_prcs)->prev->next = (*it_prcs)->next;
		(*it_prcs)->next->prev = (*it_prcs)->prev;
		(*it_prcs) = (*it_prcs)->prev->next;
		ft_printf("FREE1\n");
		free(*temp_prcs);
		return (2);
	}
	else if ((*it_prcs)->next)
	{
		(*it_prcs) = (*it_prcs)->next;
		ft_printf("FREE2\n");
		free(*temp_prcs);
		(*it_prcs)->prev = NULL;
		return (2);
	}
	else
	{
		if ((*it_prcs)->prev)
		{	
			(*it_prcs)->prev->next = NULL;
			ft_printf("FREE3\n");
			free(*temp_prcs);
		return (1);
		}
		else
		{
			ft_printf("FREE4\n");
			free(*temp_prcs);
			*it_prcs = NULL;
		return (1);
		}
	}
}

int		check_ft(t_vm *vm, t_proc **prcs)
{
	t_proc **it_prcs;
	// t_proc *prev;
	t_proc **temp_prcs;

	it_prcs = prcs;
	// prev = it_prcs;
	while ((*it_prcs))
	{
		if ((*it_prcs)->live == 0)
		{
			temp_prcs = it_prcs;
			if ((*it_prcs)->prev != NULL)
			{
				// it_prcs->prev->next = it_prcs->next;
				// it_prcs->next->prev = it_prcs->prev;
				// it_prcs = it_prcs->prev->next;
				ft_printf("it_proc %d\n", (*it_prcs)->cur_pos);
				if (ft_delete_node(it_prcs, temp_prcs) == 2)
					continue;
				else
					break;
				ft_printf("   %p  \n", *prcs);
			}
			else
			{
				// it_prcs = it_prcs->next;
				if (ft_delete_node(it_prcs, temp_prcs) == 2)
					continue;
				else
					break;
				ft_printf("   %p  \n", *prcs);
				// it_prcs->prev = NULL;
			}
		}
		(*it_prcs) = (*it_prcs)->next;
	}
	if (!(*prcs))
		return (0);
	return (1);
}