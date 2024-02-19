/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:42:42 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/01/21 21:59:36 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	prep_nextline(t_gnl_lst **lst)
{
	int		i;
	char	*new_s;

	while (*lst)
	{
		i = -1;
		while ((*lst)->cont[++i])
		{
			if ((*lst)->cont[i] == '\n' && (*lst)->cont[i + 1])
			{
				new_s = ft_strdup_gnl(&((*lst)->cont[i + 1]));
				free((*lst)->cont);
				(*lst)->cont = new_s;
				return ;
			}
		}
		clean_node(lst);
	}
	*lst = NULL;
}

char	*do_line(t_gnl_lst *lst)
{
	char	*buf;
	int		len;
	int		b;
	int		l;

	len = lst_cont_len(lst);
	buf = ft_calloc_gnl(sizeof(char), len + 1);
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

void	ft_lstadd(t_gnl_lst **lst, char *buf)
{
	t_gnl_lst	*node;
	t_gnl_lst	*head;

	node = malloc(sizeof(t_gnl_lst));
	if (!node)
		return ;
	head = *lst;
	if (!head)
		*lst = node;
	else
	{
		while (head->next)
			head = head->next;
		head->next = node;
	}
	node->cont = buf;
	node->next = NULL;
}

//create list first and all next nodes while line is the same
void	create_list(t_gnl_lst **lst, int fd)
{
	char	*buf;
	int		chars_read;

	while (!find_newline(*lst))
	{
		buf = (char *)ft_calloc_gnl(sizeof(char), BUFFER_SIZE + 1);
		if (!buf)
			return ;
		chars_read = read(fd, buf, BUFFER_SIZE);
		if (!chars_read || chars_read == -1)
		{
			free(buf);
			return ;
		}
		ft_lstadd(lst, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_gnl_lst	*lst;
	char				*line;

	if (fd < 0 || read(fd, &lst, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&lst, fd);
	if (lst == NULL)
		return (NULL);
	line = do_line(lst);
	prep_nextline(&lst);
	return (line);
}
