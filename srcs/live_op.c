/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 15:42:49 by oelbelam          #+#    #+#             */
/*   Updated: 2020/06/18 15:27:59 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int live_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
    int32_t	player_num;

	player_num = 0;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	player_num = vm->arena[(*prcs)->cur_pos] << 24 | vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE] << 16 | vm->arena[((*prcs)->cur_pos + 2) % MEM_SIZE] << 8 | vm->arena[((*prcs)->cur_pos + 3) % MEM_SIZE];
	(*prcs)->live = 1;
	player_num *= -1;
	vm->nbr_lives += 1;
	if (player_num > 0 && player_num <= vm->num_player)
		(*player)[player_num - 1].live += 1;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 4) % MEM_SIZE;
    return (1);
}