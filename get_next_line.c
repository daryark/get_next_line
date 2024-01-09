/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:42:42 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/01/09 01:45:04 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	prep_nextline(t_list **lst)
{
	int		i;
	char	*new_s;
	t_list	*tmp;

	while (*lst)
	{
		i = -1;
		while ((*lst)->cont[++i])
		{
			if ((*lst)->cont[i] == '\n' && (*lst)->cont[i + 1])
			{
				new_s = ft_strdup(&((*lst)->cont[i + 1]));
				free((*lst)->cont);
				(*lst)->cont = new_s;
				return ;
			}
		}
		tmp = (*lst)->next;
		free((*lst)->cont);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

char	*get_line_(t_list *lst)
{
	char	*buf;
	int		len;
	int		b;
	int		l;

	len = lst_cont_len(lst);
	buf = ft_calloc(sizeof(char), len + 1);
	if (!buf)
		return (NULL);
	b = 0;
	l = 0;
	while (b < len)
	{
		if (!lst->cont[l])
		{
			lst = lst->next;
			l = 0;
		}
		buf[b++] = lst->cont[l++];
	}
	return (buf);
}

//create list first and all next nodes while line is the same
void	create_list(t_list **lst, int fd)
{
	char	*buf;
	int		chars_read;

	while (!find_newline(*lst))
	{
		buf = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!buf)
			return ;
		chars_read = read(fd, buf, BUFFER_SIZE);
		if (!chars_read || chars_read == -1)
		{
			free(buf);
			return ;
		}
		ft_lstadd_back(lst, buf);
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
	line = get_line_(lst);
	prep_nextline(&lst);
	return (line);
}
