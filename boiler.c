/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boiler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:47:54 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/01/03 21:52:46 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	int		size;
	char	*ln;

	size = 0;
	fd = open("test.txt", O_RDONLY);
		ln = get_next_line(fd);
		printf("%d->%s", ++size, ln);
	// while (ln)
	// {
	// 	ln = get_next_line(fd);
	// 	printf("%d->%s", ++size, ln);
	// }
	return (0);
}
