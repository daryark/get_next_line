/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:42:42 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/01/02 20:48:06 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//create list first and all next nodes while line is the same
void	create_list(char **lst, int fd)
{
	char	*buf;
	char	*read_str;

	while (!find_newline(ft_lstlast(lst)))
	{
		buf = ft_calloc(BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
		read_str = read(fd, buf, BUFFER_SIZE);
		if (!read_str)
		{
			free(buf);
			return ;
		}
		ft_lstadd_back(&lst, ft_lstnew(buf));
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;

	if (fd < 0 || read(fd, &lst, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&lst, fd);
	if (lst == NULL)
		return (NULL);
	line =  get_line(lst);
	prep_nextline(lst);
	return (line);
}
