#include "vm.h"

int		vm_read_register(unsigned char reg[REG_SIZE])
{
	int	value;
	int	mask;
	int	i;

	value = 0;
	i = 0;
	while (i < REG_SIZE)
	{
		value = value << 8;
		mask = (int)(reg[i]);
		value = value | mask;
		i++;
	}
	return (value);
}

void	vm_store_in_register(unsigned char (*reg)[REG_SIZE], int value)
{
	int				i;

	i = REG_SIZE - 1;
	while (i >= 0)
	{
		(*reg)[i] = (unsigned char)value;
		value = value >> 8;
		i--;
	}
}