/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomnes <vomnes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 15:16:44 by vomnes            #+#    #+#             */
/*   Updated: 2017/05/05 14:19:10 by vomnes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void print_instructions_list(t_instructions *lst)
{
	t_instructions *current;

	current = lst;
	while(current != NULL)
	{
		ft_printf("=========[%d]======\n", current->num_line);
		ft_printf("is_label = %d\n", current->is_label);
		ft_printf("label_name = %s\n", current->label_name);
		ft_printf(B_GREEN"line_label = %s\n"DEF, current->line_label);
		ft_printf(B_YELLOW"line_opcode = %s\n"DEF, current->line_opcode);
		if (current->opcode > 0)
			ft_printf("opcode = %d [%s]\n", current->opcode, g_op_tab[current->opcode].name);
		else
			ft_printf("opcode = %d\n", current->opcode);
		ft_printf(B_BLUE"line_args = %s\n"DEF, current->line_args);
		current = current->next;
	}
}

void		delete_lst_instructions(t_instructions *lst)
{
	t_instructions *tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		tmp->num_line = 0;
		tmp->is_label = 0;
		ft_strdel(&tmp->line_label);
		ft_strdel(&tmp->label_name);
		ft_strdel(&tmp->line_opcode);
		ft_strdel(&tmp->line_args);
		tmp = tmp->next;
	}
	tmp = NULL;
}
