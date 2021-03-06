/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_file_champ.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 11:40:20 by atrudel           #+#    #+#             */
/*   Updated: 2017/05/23 15:50:14 by pdady            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				parse_instruction(size_t size, unsigned char buf[size],\
		t_player *player)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (player->size_player != size)
	{
		ft_dprintf(2, "Player size differs from what is written in the header");
		exit(-1);
	}
	while (i < size && buf[i] == 0)
		i++;
	while (i < size)
		player->memory[j++] = buf[i++];
}

char				**vm_read_file_champ(char **av, t_vm *vm, int no_player)
{
	int				fd;
	size_t			size;
	unsigned char	buf[PROG_NAME_LENGTH + COMMENT_LENGTH + 16];
	char			c;

	c = 0;
	size = sizeof(t_header);
	if (*av && ft_strcmp(*av, "-n") == 0)
	{
		if ((no_player = ft_lltoi(av[1])) <= 0)
			vm_error_exit(vm, "Bad entry for player number");
		av += 2;
	}
	if (open(*av, O_DIRECTORY) > 0 || (fd = open(*av, O_RDONLY)) < 0)
	{
		perror(0);
		exit(-1);
	}
	vm->nb_players += 1;
	read(fd, buf, size);
	vm_parse_header(size, buf, vm, no_player);
	size = read(fd, buf, vm->players[no_player].size_player + 16);
	parse_instruction(size, buf, &vm->players[no_player]);
	close(fd);
	return (av);
}
