/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:56:14 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/01/09 17:35:59 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	prep_nextline(t_list **lst)
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
				new_s = ft_strdup(&((*lst)->cont[i + 1]));
				free((*lst)->cont);
				(*lst)->cont = new_s;
				return ;
			}
		}
		clean_node(lst);
	}
	*lst = NULL;
}

char	*do_line(t_list *lst)
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

void	ft_lstadd_back(t_list **lst, char *buf)
{
	t_list	*node;
	t_list	*head;

	node = malloc(sizeof(t_list));
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
		if (!chars_read)
		{
			free(buf);
			return ;
		}
		ft_lstadd_back(lst, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst[OPEN_MAX];
	char			*line;

	if (fd < 0 || read(fd, &lst[fd], 0) < 0 || BUFFER_SIZE <= 0)
	{
		if (lst[fd])
			clean_node(&lst[fd]);
		return (NULL);
	}
	create_list(&lst[fd], fd);
	if (lst[fd] == NULL)
		return (NULL);
	line = do_line(lst[fd]);
	prep_nextline(&lst[fd]);
	return (line);
}
