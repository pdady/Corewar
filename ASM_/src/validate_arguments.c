/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomnes <vomnes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 19:25:35 by vomnes            #+#    #+#             */
/*   Updated: 2017/05/11 10:47:45 by vomnes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	print_arg_error(t_args *current, int opcode, int num_line, \
int num_arg)
{
	if (current->type == REG_CODE)
		ft_dprintf(2, "Invalid parameter %d type %s for instruction '%s' \
- Line %d\n", num_arg + 1, "register", g_op_tab[opcode].name, num_line);
	else if (current->type == IND_CODE)
		ft_dprintf(2, "Invalid parameter %d type %s for instruction '%s' \
- Line %d\n", num_arg + 1, "indirect", g_op_tab[opcode].name, num_line);
	else if (current->type == DIR_CODE)
		ft_dprintf(2, "Invalid parameter %d type %s for instruction '%s' \
- Line %d\n", num_arg + 1, "direct", g_op_tab[opcode].name, num_line);
	return (-1);
}

static int	check_each_arg(t_instructions *lst, int opcode, int num_line)
{
	t_args	*current;
	int		num_arg;
	int		code;

	num_arg = 0;
	current = lst->arg;
	code = 0;
	while (current != NULL)
	{
		if ((code = (g_op_tab[opcode].arg_types[num_arg] & \
		current->t_arg)) == 0)
			return (print_arg_error(current, opcode, num_line, num_arg));
		current = current->next;
		num_arg++;
	}
	return (0);
}

/*
** validate_arguments : Check if the arguments for an opcode used are allowed.
** Example :
** code = g_op_tab[opcode].arg_types[num_arg] & current->t_arg
** ---> code = (T_REG | T_DIR) & T_IND;
** If the result is NULL the argument used is unauthorised
** else it is authorised.
*/

int			validate_arguments(t_instructions **lst)
{
	t_instructions *current;

	current = *lst;
	while (current != NULL)
	{
		if (current->line_args)
		{
			if (check_each_arg(current, current->opcode, \
			current->num_line) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
