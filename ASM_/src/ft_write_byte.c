/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_byte.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomnes <vomnes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:46:42 by vomnes            #+#    #+#             */
/*   Updated: 2017/05/09 18:22:56 by vomnes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_write_byte(int fd, unsigned int value, char nb_octet)
{
	int		byte_offset;
	char	octet;

	octet = 0;
	byte_offset = 8 * (nb_octet - 1);
	while (byte_offset >= 0)
	{
		octet = (value >> byte_offset) & 0xFF;
		write(fd, &octet, 1);
		byte_offset -= 8;
	}
}
