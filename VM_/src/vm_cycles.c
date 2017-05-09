#include "vm.h"

static void	vm_advance_processes_one_cycle(t_vm *vm)
{
	unsigned int	pc;
	t_process		*process;

	process = vm->processes;
	while (process && process->next)
		process = process->next;
	while (process)
	{
		if (process->alive)
		{
			pc = vm_read_register(process->pc);
			if (!process->instruction.opcode)
				process->instruction = vm_read_opcode(vm, pc);
			process->instruction.cycles_to_execution -= 1;
			if (process->instruction.cycles_to_execution == 0)
			{
				vm_decode_parameter_byte(process, vm);
				process->instruction.op(process, vm);
				ft_bzero(&process->instruction, sizeof(t_instruction));
			}
		}
		process = process->prev;
	}
}

static void	vm_check_lives_and_kill(t_vm *vm)
{
	static int	check_count = 0;
	t_process	*current;

	check_count += 1;
	current = vm->processes;
	while (current)
	{
		if (current->nb_lives < 1)
			current->alive = 0;
		current->nb_lives = 0;
		current = current->next;
	}
	if (vm->nb_lives_since_last_check >= NBR_LIVE || check_count >= MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		check_count = 0;
	}
	vm->nb_lives_since_last_check = 0;
}

/*
**	Does one cycle in the game.
**	Returns 1 if the game is still running after the cycle.
**	Returns 0 if the game is over (i.e. all processes are dead);
*/

int			vm_do_one_cycle(t_vm *vm)
{
	static int	cycles_since_last_check = 0;
	t_process	*current;

	vm->cycle_nbr += 1;
	cycles_since_last_check += 1;
	vm_advance_processes_one_cycle(vm);
	if (cycles_since_last_check >= vm->cycle_to_die)
	{
		vm_check_lives_and_kill(vm);
		cycles_since_last_check = 0;
	}
	current = vm->processes;
	while (current)
	{
		if (current->alive && !(vm->dumps && vm->dumps == vm->cycle_nbr))
			return (1);
		current = current->next;
	}
	if (vm->dumps && vm->dumps == vm->cycle_nbr)
	{
		print_memory_dump(*vm);
		// delete DATA
		exit(0);
	}
	return (0);
}