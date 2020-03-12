/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 10:41:03 by oelbelam          #+#    #+#             */
/*   Updated: 2020/03/09 12:50:09 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <ncurses.h>

void visu(t_vm *vm, t_proc *proc)
{
	initscr();
	cbreak();
    noecho();
	WINDOW *win = newwin(66,195,1, 1);
	WINDOW *winmenu = newwin(66,66,1, 196);
	start_color();
	init_pair(1,COLOR_GREEN,COLOR_BLACK);
	init_pair(2,COLOR_RED,COLOR_BLACK);
	init_pair(3,COLOR_BLUE,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	refresh();
	box(win,0,0);
    box(winmenu,0,0);
	int i = 1;
	int f = 1;
	int h = 1;
	keypad(win, true);
	t_proc *it_proc;
	while(i <= 4096)
	{
		it_proc = proc;
		if (vm->ar_clr[i - 1])
		{
			wattron(win,COLOR_PAIR(vm->ar_clr[i - 1]));
			mvwprintw(win,f,h," %02x", vm->arena[i - 1]); 
			wattroff(win, COLOR_PAIR(vm->ar_clr[i - 1]));
		}
		else
			mvwprintw(win,f,h," %02x", vm->arena[i - 1]);
		while (it_proc)
		{
			if (it_proc->cur_pos == i - 1)
			{
				mvwprintw(win,f,h," ");
				wattron(win,A_REVERSE | COLOR_PAIR(vm->ar_clr[i - 1]));
				mvwprintw(win,f,h+1,"%02x", vm->arena[i - 1]);
				wattroff(win,A_REVERSE | COLOR_PAIR(vm->ar_clr[i - 1]));
			}
			it_proc = it_proc->next;
		}
		if(i % 64 == 0 && i != 0)
		{
			h = 1;
			f++;
		}
		else
			h = h + 3;
		i++;
	}
	wrefresh(win);
	wrefresh(winmenu);
	int ch;
	timeout(2000);
	ch = getch();
	if (ch == KEY_ENTER)
	{
		// timeout(2000);
		while (1)
		{
			getch();
			break ;
		}
	}
	// endwin();
}